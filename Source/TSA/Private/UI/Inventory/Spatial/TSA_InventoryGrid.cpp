// Dark Trace Studio Works


#include "UI/Inventory/Spatial/TSA_InventoryGrid.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "UI/Inventory/GridSlots/TSA_GridSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "Systems/InventorySystem/Utils/TSA_InventoryStatics.h"
#include "Utils/TSA_WidgetUtils.h"

void UTSA_InventoryGrid::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}

void UTSA_InventoryGrid::AddItem(UTSA_InventoryItem* Item)
{
	
}

void UTSA_InventoryGrid::InitializeGrid(UTSA_InventoryComponent* InventoryComponent)
{
	OwnerComponent = InventoryComponent;
	OwnerComponent->OnItemAdded.AddDynamic(this, &UTSA_InventoryGrid::AddItem);
	ConstructGrid(InventoryComponent->GetRows(), InventoryComponent->GetColumns());
	// TODO:显示库存物品
}

void UTSA_InventoryGrid::ConstructGrid(int32 Rows, int32 Columns)
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
