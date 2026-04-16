// Dark Trace Studio Works


#include "UI/Inventory/GridSlots/TSA_QuickSlot.h"

#include "TSA_GameplayTags.h"
#include "Components/Image.h"
#include "Items/DataTable/TSA_ItemData.h"
#include "Utils/TSA_ItemUtils.h"
#include "Items/TSA_InventoryItem.h"

void UTSA_QuickSlot::InitSlot(int32 InSlotIndex)
{
	SlotIndex = InSlotIndex;
	if (Brush_Unoccupied.IsSet())
	{
		Image_QuickSlot->SetBrush(Brush_Unoccupied);
	}
}

void UTSA_QuickSlot::SetQuickSlot(UTSA_InventoryItem* InItem)
{
	if (!InItem) return;
	
	CurrentModule = InItem;
	
	FTSA_ItemDataRow ItemData;
	UTSA_ItemUtils::GetItemStaticDataFromItem(InItem, ItemData);
	if (ItemData.Icon)
	{
		Image_QuickSlot->SetBrushFromTexture(ItemData.Icon);
	}
	
	IsEmpty = false;
}

void UTSA_QuickSlot::ClearQuickSlot()
{
	CurrentModule = nullptr;
	Image_QuickSlot->SetBrush(Brush_Unoccupied);
	IsEmpty = true;
}
