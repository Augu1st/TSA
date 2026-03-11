#pragma once

#include "TSA_GridTypes.generated.h"

class UTSA_InventoryItem;

UENUM()
enum class ETSA_GridType : uint8
{
	General,	// 通用
	Equipment,	// 装备
	Prop,		// 道具
	Collection	// 收集品
};

USTRUCT()
struct FTSA_SlotAvailability
{
	GENERATED_BODY()

	FTSA_SlotAvailability() {}
	FTSA_SlotAvailability(int32 ItemIndex, int32 Room, bool bHasItem) : Index(ItemIndex), AmountToFill(Room), bItemAtIndex(bHasItem) {}

	int32 Index = INDEX_NONE;
	int32 AmountToFill = 0;
	bool bItemAtIndex = false;
};

USTRUCT()
struct FTSA_SlotAvailabilityResult
{
	GENERATED_BODY()
	
	FTSA_SlotAvailabilityResult() {}
	
	TWeakObjectPtr<UTSA_InventoryItem> Item;
	int32 TotalRoomToFill = 0;
	int32 Remainder = 0;
	bool bStackable = false;
	TArray<FTSA_SlotAvailability> SlotAvailabilities;
};
