// Dark Trace Studio Works


#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"

#include "TSA_GameplayTags.h"
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

bool UTSA_InventoryComponent::TryAddItem(UTSA_ItemComponent* ItemComponent)
{
	FTSA_SlotAvailabilityResult Result = HasRoomForItem(ItemComponent);
	
	// 情况1： 背包已满
	if (Result.TotalRoomToFill == 0)
	{
		UTSA_UIMessageSubsystem* MsgSys = UTSA_MessageUtils::GetUIMessageSubsystem(GetOwner());
		MsgSys->BroadcastUIMessage(FText::FromString(TEXT("背包空间不足！")));
		return  false;
	}
	
	// 情况2： 背包已存在相同物品
	if (Result.Item.IsValid() && Result.bStackable)
	{
		Server_AddStacksToItem(ItemComponent,Result.TotalRoomToFill,Result.Remainder);
	}
	// 情况3： 背包无相同物品 或 物品不可堆叠
	else
	{
		Server_AddNewItem(ItemComponent,Result.bStackable ? Result.TotalRoomToFill : 0);
	}
	return true;
}

void UTSA_InventoryComponent::Server_AddNewItem_Implementation(UTSA_ItemComponent* ItemComponent, int32 StackCount)
{
	const int32 EmptyIndex = InventoryList.FindFirstEmptySlot(MaxCapacity);
	if (EmptyIndex == -1) return;
	
	UTSA_InventoryItem* NewItem = InventoryList.AddEntry(ItemComponent,EmptyIndex);
	
	if (GetOwner()->GetNetMode() == ENetMode::NM_ListenServer || GetOwner()->GetNetMode() == ENetMode::NM_Standalone)
	{
		OnItemAdded.Broadcast(NewItem);
	}
}

void UTSA_InventoryComponent::Server_AddStacksToItem_Implementation(UTSA_ItemComponent* ItemComponent, int32 StackCount,
	int32 Remainder)
{
	
}

void UTSA_InventoryComponent::AddRepSubObj(UObject* SubObj)
{
	if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && SubObj)
	{
		AddReplicatedSubObject(SubObj);
	}
}

FTSA_SlotAvailabilityResult UTSA_InventoryComponent::HasRoomForItem(UTSA_ItemComponent* ItemComponent)
{
	FGameplayTag ItemCategory = UTSA_ItemUtils::GetItemCategoryFromItemComp(ItemComponent);
	if (!MatchItemCategory(ItemCategory)) return FTSA_SlotAvailabilityResult();
	
	return FTSA_SlotAvailabilityResult();
}

UTSA_InventoryItem* UTSA_InventoryComponent::GetItemAtIndex(int32 Index) const
{
	return InventoryList.GetItemAtSlot(Index);
}

void UTSA_InventoryComponent::RequestMoveItem(int32 FromIndex, int32 ToIndex)
{
	// 如果是客户端，发送 RPC 给服务器
	if (GetOwnerRole() < ROLE_Authority)
	{
		Server_MoveItem(FromIndex, ToIndex);
	}
	else // 如果本身就是服务器，直接执行
	{
		InventoryList.MoveItem(FromIndex, ToIndex);
		// 这里可以触发委托通知 UI 刷新
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

void UTSA_InventoryComponent::Server_MoveItem_Implementation(int32 FromIndex, int32 ToIndex)
{
	InventoryList.MoveItem(FromIndex, ToIndex);
}



