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
	void PreReplicatedRemove(const TArrayView<int32> RemovedIndices, int32 FinalSize);
	// End of FFastArraySerializer contract
	bool NetDeltaSerialize(FNetDeltaSerializeInfo& DeltaParams)
	{
		return FastArrayDeltaSerialize<FTSA_InventoryEntry, FTSA_InventoryFastArray>(Entries, DeltaParams, *this);
	}
	
	UTSA_InventoryItem* AddEntry(const UTSA_ItemComponent* ItemComponent, int32 SlotIndex);
	UTSA_InventoryItem* AddEntry(UTSA_InventoryItem* Item, int32 SlotIndex);
	void RemoveEntry(UTSA_InventoryItem* Item);
	
	// 获取指定格子里的物品
	UTSA_InventoryItem* GetItemAtSlot(int32 SlotIndex) const;
	// 寻找第一个空位（需要传入背包总容量）
	int32 FindFirstEmptySlot(int32 MaxCapacity) const;
	// 移动或交换物品位置
	bool MoveItem(int32 FromSlot, int32 ToSlot);
	
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
