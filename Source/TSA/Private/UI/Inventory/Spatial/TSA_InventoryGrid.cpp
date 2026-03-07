// Dark Trace Studio Works


#include "UI/Inventory/Spatial/TSA_InventoryGrid.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "UI/Inventory/GridSlots/TSA_GridSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Utils/TSA_WidgetUtils.h"

void UTSA_InventoryGrid::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	ConstructGrid();
}

void UTSA_InventoryGrid::ConstructGrid()
{
	GridSlots.Reserve(Rows * Columns);

	for (int32 j = 0; j < Rows; ++j)
	{
		for (int32 i = 0; i < Columns; ++i)
		{
			UTSA_GridSlot* GridSlot = CreateWidget<UTSA_GridSlot>(this, GridSlotClass);
			CanvasPanel->AddChild(GridSlot);
			
			const FIntPoint SlotPos = FIntPoint(i, j);
			GridSlot->SetSlotIndex(UTSA_WidgetUtils::GetIndexFromPosition(SlotPos, Columns));
			
			UCanvasPanelSlot* GridCPS = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridSlot);
			GridCPS->SetSize(FVector2D(SlotSize));
			GridCPS->SetPosition(SlotPos*SlotSize);
			
			GridSlots.Add(GridSlot);
		}
	}
}
