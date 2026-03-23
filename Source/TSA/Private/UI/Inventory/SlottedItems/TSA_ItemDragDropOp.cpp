// Dark Trace Studio Works


#include "UI/Inventory/SlottedItems/TSA_ItemDragDropOp.h"

#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"

void UTSA_ItemDragDropOp::DragCancelled_Implementation(const FPointerEvent& PointerEvent)
{
	Super::DragCancelled_Implementation(PointerEvent);
	
	if (PointerEvent.GetEffectingButton() != EKeys::LeftMouseButton) return;
	
	if (SourceInventory.IsValid() && SourceSlotIndex != -1)
	{
		SourceInventory->RequestDropItemIntoWorld(SourceSlotIndex);
	}
}
