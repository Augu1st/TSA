
#include "Systems/InventorySystem/FastArray/TSA_FastArray.h"
#include "Items/TSA_InventoryItem.h"
#include "Items/Component/TSA_ItemComponent.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "TSA/TSA.h"
#include "Utils/TSA_ItemUtils.h"

void FTSA_InventoryFastArray::PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize)
{
	UTSA_InventoryComponent* IC = Cast<UTSA_InventoryComponent>(OwnerComponent);
	if (!IsValid(IC)) return;
    	
	for (int32 Index : AddedIndices)
	{
		if (Entries[Index].Item != nullptr)
		{
			IC->OnItemAdded.Broadcast(Entries[Index].Item, Entries[Index].SlotIndex);
		}
	}
}

void FTSA_InventoryFastArray::PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize)
{
	UTSA_InventoryComponent* IC = Cast<UTSA_InventoryComponent>(OwnerComponent);
	if (!IsValid(IC)) return;

	for (int32 Index : ChangedIndices)
	{
		// 当原本为空的指针，终于接收到服务器传来的 UObject 时，触发广播！
		if (Entries[Index].Item != nullptr)
		{
			IC->OnItemChanged.Broadcast(Entries[Index].Item, Entries[Index].SlotIndex);
		}
	}
}

void FTSA_InventoryFastArray::PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize)
{
	UTSA_InventoryComponent* IC = Cast<UTSA_InventoryComponent>(OwnerComponent);
	if (!IsValid(IC)) return;
    	
	for (int32 Index : RemovedIndices)
	{
		IC->OnItemRemoved.Broadcast(Entries[Index].Item,Entries[Index].SlotIndex);
	}
}

UTSA_InventoryItem* FTSA_InventoryFastArray::AddEntry(const FInstancedStruct& ItemManifestStruct, int32 SlotIndex)
{
	// 1. 基础校验
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	
	// 2. 校验传入的 FInstancedStruct 是否有效 (是不是空的)
	if (!ItemManifestStruct.IsValid())
	{
		return nullptr;
	}

	// 3. 直接在这里创建 UObject (UTSA_InventoryItem)
	UTSA_InventoryItem* NewItemObject = NewObject<UTSA_InventoryItem>(OwnerComponent, UTSA_InventoryItem::StaticClass());

	// 4. 将完整的 FInstancedStruct 塞进 UObject
	// 此时无论是装备的耐久度，还是道具的数量，都完美无损地传进去了！
	NewItemObject->SetItemManifest(ItemManifestStruct);

	// 5. 添加到 FastArray 数组中
	FTSA_InventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Item = NewItemObject;
	NewEntry.SlotIndex = SlotIndex;

	// 6. 注册网络同步子对象
	UTSA_InventoryComponent* IC = Cast<UTSA_InventoryComponent>(OwnerComponent);
	if (IsValid(IC))
	{
		IC->AddRepSubObj(NewEntry.Item);
	}
    
	// 7. 标记 FastArray 脏了，触发网络同步
	MarkItemDirty(NewEntry);

	return NewEntry.Item;
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


void FTSA_InventoryFastArray::MarkItemDirtyByPtr(UTSA_InventoryItem* Item)
{
	for (FTSA_InventoryEntry& Entry : Entries)
	{
		if (Entry.Item == Item)
		{
			MarkItemDirty(Entry); // 引擎底层函数，强制同步此项
			return;
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

TArray<TTuple<UTSA_InventoryItem*, int32>> FTSA_InventoryFastArray::FindItemsAndSlotsByHandle(const FDataTableRowHandle& ItemHandle) const
{
	TArray<TTuple<UTSA_InventoryItem*, int32>> FoundResults;
	
	// 预分配内存，避免数组扩容开销
	FoundResults.Reserve(Entries.Num());

	for (const FTSA_InventoryEntry& Entry : Entries)
	{
		if (!Entry.Item) continue;
		
		const FTSA_ItemManifest& Manifest = Entry.Item->GetItemManifest();
		if (Manifest.ItemDataHandle.DataTable == ItemHandle.DataTable && 
			Manifest.ItemDataHandle.RowName == ItemHandle.RowName)
		{
			// Emplace 直接在数组内存中构造 TTuple，连拷贝构造函数都省了！(极致优化)
			FoundResults.Emplace(Entry.Item, Entry.SlotIndex);
		}
	}

	return FoundResults;
}

int32 FTSA_InventoryFastArray::GetItemIndex(UTSA_InventoryItem* Item) const
{
	for (int32 i = 0; i < Entries.Num(); ++i)
	{
		if (Entries[i].Item == Item)
		{
			return Entries[i].SlotIndex;
		}
	}
	return -1;
}
