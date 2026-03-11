#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"

#include "TSA_FastArray.generated.h"

class UTSA_ItemComponent;
class UTSA_InventoryItem;
class UTSA_InventoryComponent;

// A single item in an inventory
USTRUCT(BLueprintType)
struct FTSA_InventoryEntry : public FFastArraySerializerItem
{
	GENERATED_BODY()
	
	FTSA_InventoryEntry() {}
	
private:
	friend UTSA_InventoryComponent;
	friend struct FTSA_InventoryFastArray;
	
	UPROPERTY()
	TObjectPtr<UTSA_InventoryItem> Item =  nullptr;
};

// List of inventory items
USTRUCT(BlueprintType)
struct FTSA_InventoryFastArray : public FFastArraySerializer
{
	GENERATED_BODY()
	
public:
	
	FTSA_InventoryFastArray() : OwnerComponent(nullptr) {}
	FTSA_InventoryFastArray(UActorComponent* InOwnerComponent) : OwnerComponent(InOwnerComponent) {}
	
	TArray<UTSA_InventoryItem*> GetAllItems() const;
	
	// FFastArraySerializer contract
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	// End of FFastArraySerializer contract
	
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FastArrayDeltaSerialize<FTSA_InventoryEntry, FTSA_InventoryFastArray>(Entries, DeltaParams, *this);
	}
	
	UTSA_InventoryItem* AddEntry(UTSA_ItemComponent* ItemComponent);
	UTSA_InventoryItem* AddEntry(UTSA_InventoryItem* Item);
	void RemoveEntry(UTSA_InventoryItem* Item);
	
private:
	friend UTSA_InventoryComponent;
	
	UPROPERTY()
	TArray<FTSA_InventoryEntry> Entries;
	
	UPROPERTY(NotReplicated)
	TObjectPtr<UActorComponent> OwnerComponent;
};

template<>
struct TStructOpsTypeTraits<FTSA_InventoryFastArray> : public TStructOpsTypeTraitsBase2<FTSA_InventoryFastArray>
{
	enum
	{
		WithNetDeltaSerializer = true
	};
};
