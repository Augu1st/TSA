
#include "Systems/InventorySystem/FastArray/TSA_FastArray.h"
#include "Items/TSA_InventoryItem.h"
#include "Items/Component/TSA_ItemComponent.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"

TArray<UTSA_InventoryItem*> FTSA_InventoryFastArray::GetAllItems() const
{
	TArray<UTSA_InventoryItem*> Results;
	Results.Reserve(Entries.Num());
	for (const auto& Entry : Entries)
	{
		if (!IsValid(Entry.Item)) continue;
		Results.Add(Entry.Item);
	}
	return Results;
}

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

UTSA_InventoryItem* FTSA_InventoryFastArray::AddEntry(UTSA_ItemComponent* ItemComponent)
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());
	UTSA_InventoryComponent* IC = Cast<UTSA_InventoryComponent>(OwnerComponent);
	if (!IsValid(IC)) return nullptr;

	FTSA_InventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Item = ItemComponent->GetItemManifest().MakeManifest(OwningActor);

	IC->AddRepSubObj(NewEntry.Item);
	MarkItemDirty(NewEntry);

	return NewEntry.Item;
}

UTSA_InventoryItem* FTSA_InventoryFastArray::AddEntry(UTSA_InventoryItem* Item)
{
	check(OwnerComponent);
	AActor* OwningActor = OwnerComponent->GetOwner();
	check(OwningActor->HasAuthority());

	FTSA_InventoryEntry& NewEntry = Entries.AddDefaulted_GetRef();
	NewEntry.Item = Item;

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
