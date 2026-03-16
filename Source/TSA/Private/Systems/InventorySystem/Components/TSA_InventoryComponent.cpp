// Dark Trace Studio Works


#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"

#include "TSA_GameplayTags.h"
#include "Items/TSA_InventoryItem.h"
#include "Systems/MessageSystem/TSA_MessageUtils.h"
#include "Systems/MessageSystem/TSA_UIMessageSubsystem.h"
#include "UI/Inventory/TSA_InventoryBase.h"
#include "Net/UnrealNetwork.h"
#include "Utils/TSA_ItemUtils.h"

UTSA_InventoryComponent::UTSA_InventoryComponent() : InventoryList(this)
{
	PrimaryComponentTick.bCanEverTick = false;
	
	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
}

void UTSA_InventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass,InventoryList);
}

bool UTSA_InventoryComponent::TryAddItem(FInstancedStruct& ItemManifestStruct)
{
	
	FTSA_SlotAvailabilityResult Result = HasRoomForItem(ItemManifestStruct);
	
	// 背包已满
	if (Result.TotalRoomToFill == 0)
	{
		Client_ShowMessage(FText::FromString(TEXT("背包空间不足！")));
		return false;
	}
	
	// 添加物品
	for (FTSA_SlotAvailability& SlotAvailability : Result.SlotAvailabilities)
	{
		if (SlotAvailability.bItemAtIndex)
		{
			AddStacksToItem(ItemManifestStruct,SlotAvailability.AmountToFill,SlotAvailability.Index);
		}
		else
		{
			AddNewItem(ItemManifestStruct,SlotAvailability.Index);
		}
	}

	return true;
}


void UTSA_InventoryComponent::AddNewItem(FInstancedStruct& ItemManifestStruct,int32 SlotIndex)
{
	if (SlotIndex == -1) return;
	
	UTSA_InventoryItem* NewItem = InventoryList.AddEntry(ItemManifestStruct,SlotIndex);
	ItemManifestStruct.GetMutable<FTSA_ItemManifestBase>().StackCount = 0;
	CurrentItemCount++;
	
	if (GetOwner()->GetNetMode() != NM_DedicatedServer)
	{
		OnItemAdded.Broadcast(NewItem, SlotIndex);	
	}
}

void UTSA_InventoryComponent::AddStacksToItem(FInstancedStruct& ItemManifestStruct, int32 AddToStack,int32 SlotIndex)
{
	FTSA_ItemManifestBase& ItemManifest = ItemManifestStruct.GetMutable<FTSA_ItemManifestBase>();
	ItemManifest.StackCount -= AddToStack;
	
	UTSA_InventoryItem* Item = InventoryList.GetItemAtSlot(SlotIndex);
	Item->GetItemManifestMutable().StackCount += AddToStack;
	
	if (GetOwner()->GetNetMode() != NM_DedicatedServer)
	{
		OnItemChanged.Broadcast(Item,SlotIndex);
	}
}

void UTSA_InventoryComponent::AddRepSubObj(UObject* SubObj)
{
	if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && SubObj)
	{
		AddReplicatedSubObject(SubObj);
	}
}

FTSA_SlotAvailabilityResult UTSA_InventoryComponent::HasRoomForItem(const FInstancedStruct& ItemManifestStruct)
{
	const FTSA_ItemManifestBase& ItemManifest = ItemManifestStruct.Get<FTSA_ItemManifestBase>();
	FGameplayTag ItemCategory = UTSA_ItemUtils::GetItemCategoryFromManifest(ItemManifest);
	if (!MatchItemCategory(ItemCategory)) return FTSA_SlotAvailabilityResult();
	
	FTSA_ItemDataRow ItemDataRow;
	if (!UTSA_ItemUtils::GetItemDataFromManifest(ItemManifest, ItemDataRow)) return FTSA_SlotAvailabilityResult();
	
	FTSA_SlotAvailabilityResult Result;
	Result.bStackable = ItemDataRow.bStackable;
	Result.TotalRoomToFill = 0;
	Result.Remainder = ItemManifest.StackCount;
	
	// 找到物品数据
	TArray<TTuple<UTSA_InventoryItem*, int32>> ExistingEntries = InventoryList.FindItemsAndSlotsByID(ItemManifest.ItemDataHandle.RowName);
	
	// 1.不可叠加 或 不存在相同物品 直接找空位
	if (!ItemDataRow.bStackable || ExistingEntries.IsEmpty())
	{
		TryAddLeftItemToEmptySlot(Result,ItemManifest.StackCount);
		return Result;
	}
	// 2.往相同物品上叠加
	for (auto Entry : ExistingEntries)
	{ 
		if (Result.Remainder == 0) return Result;
		int32 RoomToFill = ItemDataRow.MaxStackCount - Entry.Get<0>()->GetItemManifest().StackCount;
		if (RoomToFill <= 0) continue;
		RoomToFill = FMath::Min(RoomToFill, Result.Remainder);
		Result.TotalRoomToFill += RoomToFill;
		Result.Remainder -= RoomToFill;
		Result.SlotAvailabilities.Emplace(Entry.Get<1>(),RoomToFill,true);
	}
	// 3.如果还有，就找空位放下
	if (Result.Remainder > 0)
	{
		TryAddLeftItemToEmptySlot(Result,Result.Remainder);
		return Result;
	}
	return Result;
}

void UTSA_InventoryComponent::TryAddLeftItemToEmptySlot(FTSA_SlotAvailabilityResult& Result, int32 StackToAdd)
{
	int32 EmptyIndex = InventoryList.FindFirstEmptySlot(MaxCapacity);
	if (EmptyIndex == -1) return;
	Result.TotalRoomToFill += StackToAdd;
	Result.Remainder -= StackToAdd;
	Result.SlotAvailabilities.Emplace(EmptyIndex,StackToAdd,false);
}

UTSA_InventoryItem* UTSA_InventoryComponent::GetItemAtIndex(int32 Index) const
{
	return InventoryList.GetItemAtSlot(Index);
}

TArray<FTSA_ItemSearchResult> UTSA_InventoryComponent::GetAllItemEntries()
{
	TArray<FTSA_ItemSearchResult> ItemEntries;
	for (const FTSA_InventoryEntry& Entry : InventoryList.GetEntries())
	{
		ItemEntries.Emplace(Entry.Item,Entry.SlotIndex);
	}
	return ItemEntries;
}


void UTSA_InventoryComponent::Client_ShowMessage_Implementation(const FText& Message)
{
	// 只有收到 RPC 的那个客户端，才会执行这段代码！
	if (UTSA_UIMessageSubsystem* MsgSys = UTSA_MessageUtils::GetUIMessageSubsystem(GetOwner()))
	{
		MsgSys->BroadcastUIMessage(Message);
	}
}

void UTSA_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

bool UTSA_InventoryComponent::MatchItemCategory(FGameplayTag& ItemCategory) const
{
	if (InventoryCategory.MatchesTag(ItemTags::Category::General)) return true;
	return InventoryCategory.MatchesTag(ItemCategory);
}



