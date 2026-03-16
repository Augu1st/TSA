#pragma once

#include "CoreMinimal.h"
#include "Net/Serialization/FastArraySerializer.h"

#include "TSA_FastArray.generated.h"

struct FInstancedStruct;
struct FTSA_ItemManifestBase;
class UTSA_ItemComponent;
class UTSA_InventoryItem;
class UTSA_InventoryComponent;

USTRUCT(BlueprintType)
struct FTSA_ItemSearchResult
{
	GENERATED_BODY()

	// 找到的物品指针
	UPROPERTY(BlueprintReadOnly, Category = "Inventory|Search")
	UTSA_InventoryItem* Item = nullptr;

	// 它所在的格子索引
	UPROPERTY(BlueprintReadOnly, Category = "Inventory|Search")
	int32 SlotIndex = -1;
	
	// 方便 Emplace 构造
	FTSA_ItemSearchResult() {}
	FTSA_ItemSearchResult(UTSA_InventoryItem* InItem, int32 InSlotIndex) : Item(InItem), SlotIndex(InSlotIndex) {}
};

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
	
	// 【新增】记录这个物品在 UI 网格中的绝对位置 (比如 0~49)
	// -1 表示无效或未分配
	UPROPERTY()
	int32 SlotIndex = -1; 
};

// List of inventory items
USTRUCT(BlueprintType)
struct FTSA_InventoryFastArray : public FFastArraySerializer
{
	GENERATED_BODY()
	
public:
	
	FTSA_InventoryFastArray() : OwnerComponent(nullptr) {}
	FTSA_InventoryFastArray(UActorComponent* InOwnerComponent) : OwnerComponent(InOwnerComponent) {}
	
	// FFastArraySerializer contract
	void PostReplicatedAdd(const TArrayView<int32> AddedIndices, int32 FinalSize);
	void PostReplicatedChange(const TArrayView<int32> ChangedIndices, int32 FinalSize);
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	// End of FFastArraySerializer contract
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FastArrayDeltaSerialize<FTSA_InventoryEntry, FTSA_InventoryFastArray>(Entries, DeltaParams, *this);
	}
	
	UTSA_InventoryItem* AddEntry(const FInstancedStruct& ItemManifestStruct, int32 SlotIndex);
	void RemoveEntry(UTSA_InventoryItem* Item);
	const TArray<FTSA_InventoryEntry>& GetEntries() const { return Entries; }
	
	// 获取指定格子里的物品
	UTSA_InventoryItem* GetItemAtSlot(int32 SlotIndex) const;
	// 寻找第一个空位（需要传入背包总容量）
	int32 FindFirstEmptySlot(int32 MaxCapacity) const;
	// 寻找所有相同物品
	TArray<TTuple<UTSA_InventoryItem*, int32>> FindItemsAndSlotsByID(const FName& ItemID) const;
	
	
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
