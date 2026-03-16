// Dark Trace Studio Works


#include "UI/Inventory/GridSlots/TSA_GridSlot.h"

#include "Components/Image.h"


void UTSA_GridSlot::SetGridSlotState(ETSA_GridSlotState State)
{
	GridSlotState = State;
	switch (GridSlotState)
	{
		case ETSA_GridSlotState::Unoccupied:
			Image_GridSlot->SetBrush(Brush_Unoccupied);
			break;
		case ETSA_GridSlotState::Occupied:
			Image_GridSlot->SetBrush(Brush_Occupied);
			break;
		case ETSA_GridSlotState::Selected:
			Image_GridSlot->SetBrush(Brush_Selected);
			break;
		case ETSA_GridSlotState::Locked:
			Image_GridSlot->SetBrush(Brush_Locked);
			break;
		default:
			break;
	}
}
