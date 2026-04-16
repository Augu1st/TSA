// Dark Trace Studio Works


#include "UI/Inventory/Spatial/TSA_QuickGrid.h"

#include "Components/HorizontalBox.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "TSA/TSA.h"
#include "UI/Inventory/GridSlots/TSA_QuickSlot.h"

void UTSA_QuickGrid::InitQuickGrid(UTSA_InventoryComponent* InventoryComponent, int32 InMaxCapacity)
{
	if (!IsValid(InventoryComponent))
	{
		UE_LOG(LogTSA, Error, TEXT("%s: InventoryComponent is not valid"), *GetName());
		return;
	}
	BindComponent = InventoryComponent;
	
	MaxCapacity = InMaxCapacity;
	ConstructGrid(MaxCapacity);
}

void UTSA_QuickGrid::ConstructGrid(int32 SlotCount)
{
	if (!IsValid(QuickSlotClass)) return;
	for (int32 i = 0; i < SlotCount; ++i)
	{
		UTSA_QuickSlot* NewSlot = CreateWidget<UTSA_QuickSlot>(this, QuickSlotClass);
		NewSlot->InitSlot(i);
		QuickSlots.Add(NewSlot);
		HBox_Slots->AddChildToHorizontalBox(NewSlot);
	}
}
