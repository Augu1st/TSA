// Dark Trace Studio Works


#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"

#include "TSA_GameplayTags.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "GameFramework/Character.h"
#include "Items/TSA_InventoryItem.h"
#include "Items/TSA_ItemActor.h"
#include "Items/Component/TSA_ItemComponent.h"
#include "Systems/MessageSystem/TSA_MessageUtils.h"
#include "Systems/MessageSystem/TSA_UIMessageSubsystem.h"
#include "UI/Inventory/TSA_InventoryBase.h"
#include "Net/UnrealNetwork.h"
#include "Utils/TSA_CommonLibrary.h"
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

int32 UTSA_InventoryComponent::ConsumeItemStack(int32 SlotIndex, int32 AmountToConsume)
{
	if (!GetOwner()->HasAuthority() || AmountToConsume <= 0) return 0;
	
	UTSA_InventoryItem* Item = InventoryList.GetItemAtSlot(SlotIndex);
	if (!Item) return 0;
	
	FTSA_ItemManifestBase& ItemManifest = Item->GetItemManifestMutable();
	
	int32 ActualConsumed = FMath::Min(ItemManifest.StackCount,AmountToConsume);
	ItemManifest.StackCount -= ActualConsumed;
	
	if (ItemManifest.StackCount <= 0)
	{
		RemoveItem(Item,SlotIndex);
	}
	else
	{
		InventoryList.MarkItemDirtyByPtr(Item);
		if (GetOwner()->GetNetMode() != NM_DedicatedServer)
		{
			OnItemChanged.Broadcast(Item,SlotIndex);
		}
	}
	return ActualConsumed;
}

void UTSA_InventoryComponent::AddNewItem(FInstancedStruct& ItemManifestStruct,int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= MaxCapacity) return;
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
	if (SlotIndex < 0 || SlotIndex >= MaxCapacity) return;
	UTSA_InventoryItem* Item = InventoryList.GetItemAtSlot(SlotIndex);
	Item->GetItemManifestMutable().StackCount += AddToStack;
	
	FTSA_ItemManifestBase& ItemManifest = ItemManifestStruct.GetMutable<FTSA_ItemManifestBase>();
	ItemManifest.StackCount -= AddToStack;
	
	// 🌟 核心修复：告诉网络系统，这个格子的数据变了！赶快发给客户端！
	InventoryList.MarkItemDirtyByPtr(Item);
	
	if (GetOwner()->GetNetMode() != NM_DedicatedServer)
	{
		OnItemChanged.Broadcast(Item,SlotIndex);
	}
}

void UTSA_InventoryComponent::RemoveItem(UTSA_InventoryItem* Item,int32 SlotIndex)
{
	if (SlotIndex < 0 || SlotIndex >= MaxCapacity) return;
	
	InventoryList.RemoveEntry(Item);
	CurrentItemCount--;
	if (GetOwner()->GetNetMode() != NM_DedicatedServer)
	{
		OnItemRemoved.Broadcast(Item, SlotIndex);	
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
	// 物品类别不匹配直接返回空结果
	if (!MatchItemCategory(ItemCategory)) return FTSA_SlotAvailabilityResult();
	
	FTSA_ItemDataRow ItemDataRow;
	if (!UTSA_ItemUtils::GetItemDataFromManifest(ItemManifest, ItemDataRow)) return FTSA_SlotAvailabilityResult();
	
	FTSA_SlotAvailabilityResult Result;
	Result.bStackable = ItemDataRow.bStackable;
	Result.TotalRoomToFill = 0;
	Result.Remainder = ItemManifest.StackCount;
	
	// 找到物品数据
	TArray<TTuple<UTSA_InventoryItem*, int32>> ExistingEntries = InventoryList.FindItemsAndSlotsByHandle(ItemManifest.ItemDataHandle);
	
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
	
	MaxCapacity = FMath::Min(MaxCapacity,Rows*Columns);
}

void UTSA_InventoryComponent::MoveItem(int32 SourceIndex, UTSA_InventoryComponent* TargetComp,
                                                             int32 TargetIndex)
{
	UTSA_InventoryItem* SourceItem = GetItemAtIndex(SourceIndex);
	if (!SourceItem) return;
	
	FInstancedStruct PayloadManifest = SourceItem->GetItemManifestStruct();
	
	// 看看目标格子原来有没有东西
	UTSA_InventoryItem* TargetItem = TargetComp->GetItemAtIndex(TargetIndex);

	if (TargetItem == nullptr)
	{
		// 情况 A：目标格子是空的 (最常见)
		// 1. 检查目标组件是否允许放入这个物品 (类型过滤，比如武器栏不能放药水)
		FTSA_SlotAvailabilityResult TargetResult = TargetComp->HasRoomForItem(PayloadManifest);
		
		if (TargetResult.TotalRoomToFill > 0)
		{
			// 2. 目标组件同意接收！直接在目标指定的格子里生成物品
			TargetComp->AddNewItem(PayloadManifest, TargetIndex);
			
			// 3. 既然货物已经安全抵达，从我这里彻底销毁源物品！
			RemoveItem(SourceItem, SourceIndex);
		}
		else
		{
			Client_ShowMessage(FText::FromString(TEXT("无法将该物品放入目标位置！")));
		}
	}
	else
	{
		// 情况 B：目标格子已经有东西了 (堆叠或交换)
		
		// 提取目标物品的数据
		FInstancedStruct TargetManifest = TargetItem->GetItemManifestStruct();
		const FTSA_ItemManifestBase& PayloadBase = PayloadManifest.Get<FTSA_ItemManifestBase>();
		const FTSA_ItemManifestBase& TargetBase = TargetManifest.Get<FTSA_ItemManifestBase>();

		// 1. 尝试堆叠 (同种物品，且都是可堆叠的)
		if (PayloadBase.ItemDataHandle == TargetBase.ItemDataHandle)
		{
			FTSA_ItemDataRow TargetDataRow;
			if (!UTSA_ItemUtils::GetItemDataFromManifest(TargetBase, TargetDataRow)) return;
			int32 MaxStackCount = TargetDataRow.MaxStackCount;
			int32 AddStack = FMath::Min(PayloadBase.StackCount, MaxStackCount - TargetBase.StackCount);
			if (AddStack <= 0) return; 
			
			if (AddStack == PayloadBase.StackCount) RemoveItem(SourceItem, SourceIndex);
			else AddStacksToItem(TargetManifest, -AddStack, SourceIndex);
			TargetComp->AddStacksToItem(PayloadManifest, AddStack, TargetIndex);
		}
		// 2. 尝试交换位置 (Swap)
		else
		{
			// 先检查互相是否能接受对方的物品类型
			FTSA_SlotAvailabilityResult SwapTest1 = TargetComp->HasRoomForItem(PayloadManifest);
			FTSA_SlotAvailabilityResult SwapTest2 = this->HasRoomForItem(TargetManifest);

			if (SwapTest1.TotalRoomToFill > 0 && SwapTest2.TotalRoomToFill > 0)
			{
				// 互相删掉旧的
				this->RemoveItem(SourceItem, SourceIndex);
				TargetComp->RemoveItem(TargetItem, TargetIndex);

				// 互相在新位置生成对方的物品！
				TargetComp->AddNewItem(PayloadManifest, TargetIndex);
				this->AddNewItem(TargetManifest, SourceIndex);
			}
			else
			{
				Client_ShowMessage(FText::FromString(TEXT("物品类型不匹配，无法交换！")));
			}
		}
	}
}

void UTSA_InventoryComponent::DropItemIntoWorld(int32 SlotIndex)
{
	if (GetOwnerRole()!= ROLE_Authority) return;
	
	UTSA_InventoryItem* ItemToDrop = GetItemAtIndex(SlotIndex);
	if (!ItemToDrop) return;
	
	FInstancedStruct ManifestToDrop = ItemToDrop->GetItemManifestStruct();

	// 计算生成位置
	AActor* OwningActor = GetOwner();
	FVector SpawnLocation = UTSA_CommonLibrary::GetRandomLocationAtPlayerFoot(OwningActor,300.f,100.f);
	FRotator SpawnRotation = OwningActor->GetActorRotation();

	// 生成掉落物 Actor
	if (ItemActorClass)
	{
		FActorSpawnParameters SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;
		
		AActor* DroppedActor = GetWorld()->SpawnActor<ATSA_ItemActor>(ItemActorClass, SpawnLocation, SpawnRotation, SpawnParams);
		if (UTSA_ItemComponent* ItemComp = DroppedActor->FindComponentByClass<UTSA_ItemComponent>())
		{
			ItemComp->SetItemManifest(ManifestToDrop);
		}
		UE_LOG(LogTemp, Log, TEXT("Dropped Item: %s"), *ItemToDrop->GetName());
	}

	// 删除该物品
	RemoveItem(ItemToDrop, SlotIndex);
}


bool UTSA_InventoryComponent::MatchItemCategory(const FGameplayTag& ItemCategory) const
{
	if (InventoryCategory.MatchesTag(ItemTags::Category::General)) return true;
	return ItemCategory.MatchesTag(InventoryCategory);
}



