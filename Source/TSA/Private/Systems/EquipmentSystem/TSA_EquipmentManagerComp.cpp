// Dark Trace Studio Works


#include "Systems/EquipmentSystem/TSA_EquipmentManagerComp.h"

#include "AbilitySystemComponent.h"
#include "TSA_GameplayTags.h"
#include "AbilitySystem/AttributeSets/TSA_VitalAttributeSet.h"
#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Items/TSA_InventoryItem.h"
#include "Items/DataAssets/TSA_ItemDataAsset.h"
#include "Items/DataAssets/TSA_ItemFragment.h"
#include "Items/DataTable/TSA_ItemData.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "Utils/TSA_ItemUtils.h"

UTSA_EquipmentManagerComp::UTSA_EquipmentManagerComp()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
	
}

void UTSA_EquipmentManagerComp::UpdateArmor(float BaseArmor)
{
	ATSA_AgentCharacter* Agent = Cast<ATSA_AgentCharacter>(GetOwner());
	if (!Agent) return;
	UTSA_InventoryComponent* ArmorInventoryComp = Agent->GetEquipmentInventoryByCategory(ItemTags::Category::Equipment_Armor);
	UTSA_InventoryItem* EquippedArmor = ArmorInventoryComp->GetItemAtIndex(0);
	if (EquippedArmor)
	{
		FTSA_ItemManifest& ItemManifest= EquippedArmor->GetItemManifestMutable();
		ItemManifest.SetStat(AttributeTags::Armor, BaseArmor);
	}
}

// Called when the game starts
void UTSA_EquipmentManagerComp::BeginPlay()
{
	Super::BeginPlay();
	//获取装备背包组件
	ATSA_AgentCharacter* Agent = Cast<ATSA_AgentCharacter>(GetOwner());
	if (!Agent) return;
	UTSA_InventoryComponent* WeaponInventoryComp = Agent->GetEquipmentInventoryByCategory(ItemTags::Category::Equipment_Weapon);
	UTSA_InventoryComponent* ArmorInventoryComp = Agent->GetEquipmentInventoryByCategory(ItemTags::Category::Equipment_Armor);
	UTSA_InventoryComponent* ModuleInventoryComp = Agent->GetEquipmentInventoryByCategory(ItemTags::Category::Equipment_Module);
	
	if (WeaponInventoryComp)
	{
		WeaponInventoryComp->OnItemAdded.AddDynamic(this, &UTSA_EquipmentManagerComp::OnWeaponEquipped);
		WeaponInventoryComp->OnItemRemoved.AddDynamic(this, &UTSA_EquipmentManagerComp::OnWeaponUnequipped);
	}
	if (ArmorInventoryComp)
	{
		ArmorInventoryComp->OnItemAdded.AddDynamic(this, &UTSA_EquipmentManagerComp::OnArmorEquipped);
		ArmorInventoryComp->OnItemRemoved.AddDynamic(this, &UTSA_EquipmentManagerComp::OnArmorUnequipped);
	}
	if (ModuleInventoryComp)
	{
		ModuleInventoryComp->OnItemAdded.AddDynamic(this, &UTSA_EquipmentManagerComp::OnModuleEquipped);
		ModuleInventoryComp->OnItemRemoved.AddDynamic(this, &UTSA_EquipmentManagerComp::OnModuleUnequipped);
	}
}

void UTSA_EquipmentManagerComp::OnWeaponEquipped(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	
}

void UTSA_EquipmentManagerComp::OnWeaponUnequipped(UTSA_InventoryItem* Item, int32 SlotIndex)
{
}

void UTSA_EquipmentManagerComp::OnArmorEquipped(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	FTSA_ItemDataRow DataRow;
	UTSA_ItemUtils::GetItemStaticDataFromItem(Item, DataRow);
	if (UTSA_ItemDataAsset* ItemDataAsset = DataRow.ItemDataAsset.LoadSynchronous())
	{
		ATSA_AgentCharacter* Agent = Cast<ATSA_AgentCharacter>(GetOwner());
		if (!IsValid(Agent)) return;
		UTSA_AbilitySystemComponent* ASC = Agent->GetASC();
	
		ItemEffectHandles.Emplace(Item, FTSA_ActiveEffectHandles());
		
		if (const UTSA_EquipStatFragment* EquipStatFragment = ItemDataAsset->FindFragment<UTSA_EquipStatFragment>())
		{
			ApplyEquipStatFragment(Item,EquipStatFragment,ASC);
		}
		
		if (const UTSA_ArmorFragment* ArmorFragment = ItemDataAsset->FindFragment<UTSA_ArmorFragment>())
		{
			FTSA_ItemManifest& ItemManifest= Item->GetItemManifestMutable();
			float CurrentArmor = ItemManifest.GetStat(AttributeTags::Armor);
			GenerateCurrentArmor(CurrentArmor,ASC);
		}
	}
}

void UTSA_EquipmentManagerComp::OnArmorUnequipped(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	FTSA_ItemDataRow DataRow;
	UTSA_ItemUtils::GetItemStaticDataFromItem(Item, DataRow);
	if (DataRow.ItemDataAsset)
	{
		ATSA_AgentCharacter* Agent = Cast<ATSA_AgentCharacter>(GetOwner());
		if (!IsValid(Agent)) return;
		UTSA_AbilitySystemComponent* ASC = Agent->GetASC();
		
		if (DataRow.ItemDataAsset->FindFragment<UTSA_ArmorFragment>())
		{
			ASC->SetNumericAttributeBase(UTSA_VitalAttributeSet::GetArmorAttribute(),0);
		}
		
		if (ItemEffectHandles.Contains(Item))
		{
			for (FActiveGameplayEffectHandle& Handle : ItemEffectHandles[Item].ActiveEffectHandles)
			{
				ASC->RemoveActiveGameplayEffect(Handle);
			}
		}
		ItemEffectHandles.Remove(Item);
	}
}

void UTSA_EquipmentManagerComp::OnModuleEquipped(UTSA_InventoryItem* Item, int32 SlotIndex)
{
}

void UTSA_EquipmentManagerComp::OnModuleUnequipped(UTSA_InventoryItem* Item, int32 SlotIndex)
{
}

float UTSA_EquipmentManagerComp::GetAdditiveValue(const TMap<FGameplayAttribute, float>& AttributeScales,UTSA_AbilitySystemComponent* ASC)
{
	if (AttributeScales.IsEmpty()) return 0.f;
	float AdditiveValue = 0.f;
	for (auto& AttributeScale :AttributeScales)
	{
		if (!AttributeScale.Key.IsValid()) continue;// 防漏填
		AdditiveValue += ASC->GetNumericAttribute(AttributeScale.Key) * AttributeScale.Value;
	}
	return AdditiveValue;
}

void UTSA_EquipmentManagerComp::ApplyEquipStatFragment(UTSA_InventoryItem* Item,const UTSA_EquipStatFragment* Fragment,UTSA_AbilitySystemComponent* ASC)
{
	// 创建动态GE
	FName UniqueGEName = MakeUniqueObjectName(GetTransientPackage(), UGameplayEffect::StaticClass(), FName("DynamicEquipGE"));
	UGameplayEffect* DynamicGE = NewObject<UGameplayEffect>(GetTransientPackage(), UniqueGEName);
	DynamicGE->DurationPolicy = EGameplayEffectDurationType::Infinite;
	
	for (const FTSA_StatModifier& Mod : Fragment->Modifiers)
	{
		if (!Mod.Attribute.IsValid()) continue; // 防漏填

		FGameplayModifierInfo ModInfo;
		ModInfo.Attribute = Mod.Attribute;
		ModInfo.ModifierOp = Mod.ModifierOp; 
		
		float AdditiveValue = GetAdditiveValue(Mod.AttributeScales, ASC); // 计算属性加成
		float FinalValue = Mod.Value + AdditiveValue; // 计算最终值
		
		FScalableFloat ScalableFloat;
		ScalableFloat.SetValue(FinalValue);
		ModInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(ScalableFloat);

		DynamicGE->Modifiers.Add(ModInfo);
	}
	FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
	FActiveGameplayEffectHandle AppliedHandle = ASC->ApplyGameplayEffectToSelf(DynamicGE, 1.0f, Context);
	ItemEffectHandles[Item].ActiveEffectHandles.Add(AppliedHandle);
}

void UTSA_EquipmentManagerComp::GenerateCurrentArmor(float BaseArmor, UTSA_AbilitySystemComponent* ASC)
{
	FName UniqueGEName = MakeUniqueObjectName(GetTransientPackage(), UGameplayEffect::StaticClass(), FName("ArmorGE"));
	UGameplayEffect* DynamicGE = NewObject<UGameplayEffect>(GetTransientPackage(), UniqueGEName);
	DynamicGE->DurationPolicy = EGameplayEffectDurationType::Instant;
	
	FGameplayModifierInfo ModInfo;
	ModInfo.Attribute = UTSA_VitalAttributeSet::GetArmorAttribute();
	ModInfo.ModifierOp = EGameplayModOp::Additive;
	FScalableFloat ScalableFloat;
	ScalableFloat.SetValue(BaseArmor);
	ModInfo.ModifierMagnitude = FGameplayEffectModifierMagnitude(ScalableFloat);
	
	DynamicGE->Modifiers.Add(ModInfo);
	FGameplayEffectContextHandle Context = ASC->MakeEffectContext();
	ASC->ApplyGameplayEffectToSelf(DynamicGE, 1.0f, Context);
}


