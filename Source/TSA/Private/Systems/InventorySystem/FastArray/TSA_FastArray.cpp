
#include "Systems/InventorySystem/FastArray/TSA_FastArray.h"
#include "Items/TSA_InventoryItem.h"
#include "Items/Component/TSA_ItemComponent.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "TSA/TSA.h"

void FTSA_InventoryFastArray::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	UTSA_InventoryComponent* IC = Cast<UTSA_InventoryComponent>(OwnerComponent);
	if (!IsValid(IC)) return;
    	
	for (int32 Index : AddedIndices)
	{
		IC->OnItemAdded.Broadcast(Entries[Index].Item);
	}
}

void FTSA_InventoryFastArray::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	UTSA_InventoryComponent* IC = Cast<UTSA_InventoryComponent>(OwnerComponent);
	if (!IsValid(IC)) return;
    	
	for (int32 Index : RemovedIndices)
	{
		IC->OnItemRemoved.Broadcast(Entries[Index].Item);
	}
}

UTSA_InventoryItem* FTSA_InventoryFastArray::AddEntry(const UTSA_ItemComponent* ItemComponent, int32 SlotIndex)
{
	if (!IsValid(ItemComponent))
	{
		return nullptr;
	}
	
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());
	UTSA_InventoryComponent* IC = Cast<UTSA_InventoryComponent>(OwnerComponent);
	if (!IsValid(IC)) return nullptr;

	// 获取 Manifest 并检查其是否在蓝图中正确配置
	const FTSA_ItemManifestBase* ManifestPtr = ItemComponent->GetItemManifestPtr();
	if (!ManifestPtr)
	{
		UE_LOG(LogTSA, Warning, TEXT("AddEntry Failed: ItemComponent 没有配置有效的 ItemManifest！"));
		return nullptr;
	}
	
	FTSA_InventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Item = ManifestPtr->MakeManifest(OwningActor);
	NewEntry.SlotIndex = SlotIndex;

	IC->AddRepSubObj(NewEntry.Item);
	
	MarkItemDirty(NewEntry);

	return NewEntry.Item;
}

UTSA_InventoryItem* FTSA_InventoryFastArray::AddEntry(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());

	FTSA_InventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Item = Item;
	NewEntry.SlotIndex = SlotIndex;

	MarkItemDirty(NewEntry);
	
	return Item;
}

void FTSA_InventoryFastArray::RemoveEntry(UTSA_InventoryItem* Item)
{
	for (auto EntryIt = Entries.CreateIterator(); EntryIt; ++EntryIt)
	{
		FTSA_InventoryEntry& Entry = *EntryIt;
		if (Entry.Item == Item)
		{
			EntryIt.RemoveCurrent();
			MarkArrayDirty();
		}
	}
}

UTSA_InventoryItem* FTSA_InventoryFastArray::GetItemAtSlot(int32 SlotIndex) const
{
	for (const FTSA_InventoryEntry& Entry : Entries)
	{
		if (Entry.SlotIndex == SlotIndex)
		{
			return Entry.Item;
		}
	}
	return nullptr; // 这个格子是空的
}

int32 FTSA_InventoryFastArray::FindFirstEmptySlot(int32 MaxCapacity) const
{
	// 遍历所有可能的格子 (0 到 MaxCapacity - 1)
	for (int32 i = 0; i < MaxCapacity; ++i)
	{
		if (GetItemAtSlot(i) == nullptr)
		{
			return i; // 找到空位
		}
	}
	return -1; // 背包满了
}

bool FTSA_InventoryFastArray::MoveItem(int32 FromSlot, int32 ToSlot)
{
	FTSA_InventoryEntry* SourceEntry = nullptr;
	FTSA_InventoryEntry* TargetEntry = nullptr;

	// 1. 找到源格子和目标格子的 Entry
	for (FTSA_InventoryEntry& Entry : Entries)
	{
		if (Entry.SlotIndex == FromSlot) SourceEntry = &Entry;
		else if (Entry.SlotIndex == ToSlot) TargetEntry = &Entry;
	}

	if (!SourceEntry) return false; // 源格子没东西，移个寂寞

	// 2. 如果目标格子有东西，执行【交换】
	if (TargetEntry)
	{
		SourceEntry->SlotIndex = ToSlot;
		TargetEntry->SlotIndex = FromSlot;
        
		// 【关键】Fast Array 必须手动标记 Dirty，服务器才会把位置变化同步给客户端！
		MarkItemDirty(*SourceEntry);
		MarkItemDirty(*TargetEntry);
	}
	// 3. 如果目标格子是空的，直接【移动】
	else
	{
		SourceEntry->SlotIndex = ToSlot;
		MarkItemDirty(*SourceEntry);
	}

	return true;
}
