// Dark Trace Studio Works


#include "UI/Inventory/SlottedItems/TSA_SlottedItem.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/TSA_InventoryItem.h"
#include "Utils/TSA_ItemUtils.h"

void UTSA_SlottedItem::SetImageBrush(const FSlateBrush& Brush) const
{
	Image_Icon->SetBrush(Brush);
}

void UTSA_SlottedItem::SetInventoryItem(UTSA_InventoryItem* Item)
{
	InventoryItem = Item;
	FTSA_ItemDataRow ItemDataRow;
	UTSA_ItemUtils::GetItemStaticDataFromItem(Item, ItemDataRow);
	const FInstancedStruct& ItemManifestStruct = Item->GetItemManifestStruct();
	
	ETSA_ItemRarity Rarity = ItemDataRow.Rarity;
	SetBackgroundByRarity(Rarity);
	
	bIsStackable = ItemDataRow.bStackable;
	if (bIsStackable)
	{	
		MaxStackCount = ItemDataRow.MaxStackCount;
		int StackCount = ItemManifestStruct.Get<FTSA_ItemManifestBase>().StackCount;
		UpdateStackCount(StackCount);
		Text_StackCount->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Text_StackCount->SetVisibility(ESlateVisibility::Collapsed);
	}
	
}

void UTSA_SlottedItem::UpdateStackCount(int32 StackCount)
{
	if (!bIsStackable) return;
	Text_StackCount->SetText(FText::FromString(FString::FromInt(StackCount)+ "/" + FString::FromInt(MaxStackCount)));
}

void UTSA_SlottedItem::SetBackgroundByRarity(ETSA_ItemRarity Rarity)
{
	FSlateBrush Brush = Brush_Background;
	
	switch (Rarity)
	{
		case ETSA_ItemRarity::None:
			Brush.TintColor = FLinearColor::Transparent;
			break;
		case ETSA_ItemRarity::Common:
			Brush.TintColor = FLinearColor(0.9f, 0.9f, 0.9f, 0.8f);
			break;
		case ETSA_ItemRarity::Great:
			Brush.TintColor = FLinearColor(0.0f, 0.8f, 0.0f, 0.5f);
			break;
		case ETSA_ItemRarity::Rare:
			Brush.TintColor = FLinearColor(0.0f, 0.0f, 0.9f, 0.5f);
			break;
		case ETSA_ItemRarity::Epic:
			Brush.TintColor = FLinearColor(0.6f, 0.0f, 1.0f, 0.5f);
			break;
		case ETSA_ItemRarity::Legendary:
			Brush.TintColor = FLinearColor(1.f, 0.6f, 0.f, 0.5f);
			break;
		case ETSA_ItemRarity::Mythic:
			Brush.TintColor = FLinearColor(0.7f, 0.f, 0.f, 0.5f);
			break;
		case ETSA_ItemRarity::Unique:
			Brush = Brush_Colorful;
		case ETSA_ItemRarity::Destruction:
			Brush.TintColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.4f);
			break;
		default:
			break;
	}
	Image_Background->SetBrush(Brush);
}
