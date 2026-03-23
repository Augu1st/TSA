// Dark Trace Studio Works


#include "UI/Inventory/Spatial/TSA_InventoryGrid.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "UI/Inventory/GridSlots/TSA_GridSlot.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Items/TSA_InventoryItem.h"
#include "Items/DataTable/TSA_ItemData.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "TSA/TSA.h"
#include "Utils/TSA_ItemUtils.h"
#include "Utils/TSA_WidgetUtils.h"
#include "UI/Inventory/SlottedItems/TSA_SlottedItem.h"

class UTSA_SlottedItem;

void UTSA_InventoryGrid::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}

void UTSA_InventoryGrid::InitializeGrid(UTSA_InventoryComponent* InventoryComponent)
{
	if (!IsValid(InventoryComponent))
	{
		UE_LOG(LogTSA, Error, TEXT("%s: InventoryComponent is not valid"), *GetName());
		return;
	}
	
	OwnerComponent = InventoryComponent;
	OwnerComponent->OnItemAdded.AddDynamic(this, &UTSA_InventoryGrid::AddItemToIndex);
	OwnerComponent->OnItemChanged.AddDynamic(this, &UTSA_InventoryGrid::UpdateItemAtIndex);
	OwnerComponent->OnItemRemoved.AddDynamic(this, &UTSA_InventoryGrid::RemoveItemFromIndex);
	
	ConstructGrid(OwnerComponent->GetRows(), OwnerComponent->GetColumns());
	
	const TArray<FTSA_ItemSearchResult>& ItemEntries = OwnerComponent->GetAllItemEntries();
	for (int32 i = 0; i < ItemEntries.Num(); ++i)
	{
		AddItemToIndex(ItemEntries[i].Item, ItemEntries[i].SlotIndex);
	}
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
			UWidget* a = this;
			GridSlot->InitSlot(this,UTSA_WidgetUtils::GetIndexFromPosition(FIntPoint(i,j), Columns));
			
			FIntPoint SlotPos = FIntPoint(i, j) * SlotSize;
			UCanvasPanelSlot* GridCPS = UWidgetLayoutLibrary::SlotAsCanvasSlot(GridSlot);
			GridCPS->SetSize(FVector2D(SlotSize - SlotPadding * 2));
			GridCPS->SetPosition(SlotPos + FIntPoint(SlotPadding));
			GridSlots.Add(GridSlot);
		}
	}
}

void UTSA_InventoryGrid::ClearGrid()
{
	// 解除监听
	if (!OwnerComponent.IsValid())
	{
		UE_LOG(LogTSA, Error, TEXT("%s: OwnerComponent is not valid"), *GetName());
		return;
	}
	OwnerComponent->OnItemAdded.RemoveDynamic(this, &UTSA_InventoryGrid::AddItemToIndex);
	OwnerComponent->OnItemChanged.RemoveDynamic(this, &UTSA_InventoryGrid::UpdateItemAtIndex);
	OwnerComponent->OnItemRemoved.RemoveDynamic(this, &UTSA_InventoryGrid::RemoveItemFromIndex);
	OwnerComponent = nullptr;
	
	// 清理Slotted Item
	for (auto& GridSlot : GridSlots)
	{
		GridSlot->ClearItemWidget();
	}
	GridSlots.Empty();
}

void UTSA_InventoryGrid::AddItemToIndex(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	if (!OwnerComponent.IsValid())
	{
		UE_LOG(LogTSA, Error, TEXT("%s: InventoryComponent is not valid"), *GetName());
		return;
	}
	
	UTSA_SlottedItem* SlottedItem = CreateWidget<UTSA_SlottedItem>(GetOwningPlayer(), SlottedItemClass);
	SetupSlottedItem(Item,SlotIndex,SlottedItem);
	
	GridSlots[SlotIndex]->SetItemWidget(SlottedItem);
	
	SlottedItems.Add(SlotIndex, SlottedItem);
	GridSlots[SlotIndex]->SetGridSlotState(ETSA_GridSlotState::Occupied);
}

void UTSA_InventoryGrid::UpdateItemAtIndex(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	UTSA_SlottedItem* SlottedItem = SlottedItems[SlotIndex];
	SlottedItem->UpdateStackCount(Item->GetItemManifest().StackCount);
}

void UTSA_InventoryGrid::RemoveItemFromIndex(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	GridSlots[SlotIndex]->ClearItemWidget();
	SlottedItems.Remove(SlotIndex);
}

void UTSA_InventoryGrid::SetupSlottedItem(UTSA_InventoryItem* Item, int32 SlotIndex,UTSA_SlottedItem* SlottedItem)
{
	SetSlottedItemImage(Item, SlottedItem);
	SlottedItem->SetInventoryItem(Item);
	SlottedItem->SetSlotIndex(SlotIndex);
}

void UTSA_InventoryGrid::SetSlottedItemImage(UTSA_InventoryItem* Item, UTSA_SlottedItem* SlottedItem)
{
	FTSA_ItemDataRow ItemDataRow;
	if (!UTSA_ItemUtils::GetItemStaticDataFromItem(Item, ItemDataRow))
	{
		UE_LOG(LogTSA, Error, TEXT("%s: Failed to get %s static data"), *GetName(), *Item->GetName());
		return;
	}
	FSlateBrush Brush;
	Brush.SetResourceObject(ItemDataRow.Icon);
	Brush.DrawAs = ESlateBrushDrawType::Image;
	Brush.ImageSize = FVector2D(SlotSize - SlotPadding);
	
	SlottedItem->SetImageBrush(Brush);
}

UTSA_InventoryComponent* UTSA_InventoryGrid::GetOwnerComponent() const
{
	return OwnerComponent.Get();
}

