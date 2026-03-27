// Dark Trace Studio Works


#include "UI/Inventory/SlottedItems/TSA_ItemDragDropOp.h"

#include "Player/TSA_PlayerController.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "TSA/TSA.h"

void UTSA_ItemDragDropOp::DragCancelled_Implementation(const FPointerEvent& PointerEvent)
{
	Super::DragCancelled_Implementation(PointerEvent);
	
	if (PointerEvent.GetEffectingButton() != EKeys::LeftMouseButton) return;
	
	if (SourceInventory.IsValid() && SourceSlotIndex != -1)
	{
		APlayerController* PC = GetWorld()->GetFirstPlayerController();
		if (ATSA_PlayerController* TSAPC = Cast<ATSA_PlayerController>(PC))
		{
			// 让控制器帮忙发丢弃请求
			TSAPC->RequestDropItem(SourceInventory.Get(), SourceSlotIndex);
			UE_LOG(LogTSA, Warning, TEXT("DragCancelled_Implementation"));
		}
	}
}
