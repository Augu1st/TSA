// Dark Trace Studio Works


#include "Systems/EquipmentSystem/TSA_BondManagerComp.h"

#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "Items/TSA_InventoryItem.h"
#include "Items/DataAssets/TSA_ItemDataAsset.h"
#include "Items/Manifest/TSA_ItemManifest.h"
#include "Utils/TSA_ItemUtils.h"

UTSA_BondManagerComp::UTSA_BondManagerComp()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UTSA_BondManagerComp::BeginPlay()
{
	Super::BeginPlay();
	
	ATSA_AgentCharacter* Agent = Cast<ATSA_AgentCharacter>(GetOwner());
	if (!Agent) return;
	InitInventoryBonding(Agent);
	
}

void UTSA_BondManagerComp::InitInventoryBonding(ATSA_AgentCharacter* Agent)
{
	UTSA_InventoryComponent* ConnectorInventory = Agent->GetConnectorInventory();
	if (ConnectorInventory)
	{
		ConnectorInventory->OnItemAdded.AddDynamic(this, &UTSA_BondManagerComp::OnConnectorAddItem);
		ConnectorInventory->OnItemRemoved.AddDynamic(this, &UTSA_BondManagerComp::OnConnectorRemoveItem);
	}
}

void UTSA_BondManagerComp::OnConnectorAddItem(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	if (!IsValid(Item)) return;
	
	FTSA_ItemDataRow ItemDataRow;
	UTSA_ItemUtils::GetItemStaticDataFromItem(Item, ItemDataRow);
	if (ItemDataRow.BondTags.IsEmpty()) return;
	
	bool bHasSameItem = false;
	for (auto InItem : ItemsInConnector)
	{
		if (UTSA_ItemUtils::CheckItemTypes(Item,InItem))
		{
			bHasSameItem = true;
			break;
		}
	}
	ItemsInConnector.Add(Item);
	if (!bHasSameItem)
	{
		RecalculateBonds();
	}
}

void UTSA_BondManagerComp::OnConnectorRemoveItem(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	if (!IsValid(Item)) return;
	
	FTSA_ItemDataRow ItemDataRow;
	UTSA_ItemUtils::GetItemStaticDataFromItem(Item, ItemDataRow);
	if (ItemDataRow.BondTags.IsEmpty()) return;
	
	ItemsInConnector.Remove(Item);
	
	bool bHasSameItem = false;
	for (auto& InItem : ItemsInConnector)
	{
		if (UTSA_ItemUtils::CheckItemTypes(Item,InItem))
		{
			bHasSameItem = true;
			break;
		}
	}
	if (!bHasSameItem)
	{
		RecalculateBonds();
	}
}

void UTSA_BondManagerComp::RecalculateBonds()
{
	ATSA_AgentCharacter* Agent = Cast<ATSA_AgentCharacter>(GetOwner());
	if (!Agent->GetASC())return;
	
	ActiveBondCounts.Empty();
	PendingBondCounts.Empty();
	
	// 清除旧GE
	for (auto& Handle : ActiveBondEffects)
	{
		Agent->GetASC()->RemoveActiveGameplayEffect(Handle);
	}
	
	// 清除旧GA？
	
	// 计算羁绊数量
	TMap<FGameplayTag,int32> BondCounts;
	TArray<FDataTableRowHandle> ItemDataRows;
	for (auto& Item : ItemsInConnector)
	{
		FTSA_ItemManifestBase& ItemManifest = Item->GetItemManifestMutable();
		bool bHasSameItem = false;
		for (auto& Row : ItemDataRows)
		{
			if (Row.DataTable == ItemManifest.ItemDataHandle.DataTable && Row.RowName == ItemManifest.ItemDataHandle.RowName)
			{
				bHasSameItem = true;
				break;
			}
		}
		if (bHasSameItem) continue;
		ItemDataRows.Add(ItemManifest.ItemDataHandle);
		const FString ContextString = { "Item" };
		FGameplayTagContainer BondTags = ItemManifest.ItemDataHandle.GetRow<FTSA_ItemDataRow>(ContextString)->BondTags;
		for (auto& Tag : BondTags)
		{
			BondCounts.FindOrAdd(Tag) += 1;
			PendingBondCounts.FindOrAdd(Tag) += 1;
		}
	}
	
	// 计算达到触发数量的羁绊
	for (const auto& Pair : BondCounts)
	{
		FGameplayTag CurrentTag = Pair.Key;
		int32 CurrentCount = Pair.Value;
		FTSA_BondDefinition BondDefinition;
		if (UTSA_ItemUtils::GetBondDefinition(this,CurrentTag, BondDefinition))
		{
			if (BondDefinition.BondTiers.Num()>0 && CurrentCount >= BondDefinition.BondTiers[0].RequiredCount)
			{
				ActiveBondCounts.FindOrAdd(CurrentTag) = CurrentCount;
			}
		}
	}
	
	// 发放羁绊效果
	FGameplayTagContainer CanActiveBonds;
	for (const auto& Pair : ActiveBondCounts)
	{
		CanActiveBonds.AddTag(Pair.Key);
	}
	for (const auto& Pair : ActiveBondCounts)
	{
		FGameplayTag CandidateTag = Pair.Key;
		
		FTSA_BondDefinition BondDef;
		if (!UTSA_ItemUtils::GetBondDefinition(this,CandidateTag, BondDef))continue;
		
		// 可激活羁绊中是否有逆羁绊
		if (CanActiveBonds.HasAny(BondDef.AntiBondTags))
		{
			ActiveBondCounts.Remove(CandidateTag);
			continue;
		}
		// 从待触发羁绊中移除
		PendingBondCounts.Remove(CandidateTag);
		
		// 激活羁绊
		int32 Count = BondCounts[CandidateTag];
		TSubclassOf<UGameplayEffect> ActivateEffect;
		for (const FTSA_BondTier& Tier : BondDef.BondTiers)
		{
			// 只激活最高层级
			if (Count >= Tier.RequiredCount) ActivateEffect = Tier.BondEffect;
		}
		if (ActivateEffect)
		{
			FActiveGameplayEffectHandle Handle = Agent->GetASC()->ApplyGameplayEffectToSelf(ActivateEffect.GetDefaultObject(),1.f,Agent->GetASC()->MakeEffectContext());
			ActiveBondEffects.Add(Handle);
		}
	}
	FTSA_BondCounts BondCountsWrapper;
	BondCountsWrapper.ActiveBondCounts = ActiveBondCounts;
	BondCountsWrapper.PendingBondCounts = PendingBondCounts;
	OnBondChanged.Broadcast(BondCountsWrapper);
}

