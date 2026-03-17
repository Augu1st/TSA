// Dark Trace Studio Works


#include "UI/Inventory/SlottedItems/TSA_SlottedItem.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "Items/TSA_InventoryItem.h"
#include "UI/Inventory/SlottedItems/TSA_ItemDragDropOp.h"
#include "Utils/TSA_ItemUtils.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"

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

FReply UTSA_SlottedItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	
	// 只响应左键拖拽
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		// 如果左键按住并且鼠标发生了位移，请调用 NativeOnDragDetected
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UTSA_SlottedItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
	if (!InventoryItem.IsValid()) return;
	// 1. 创建我们的专属快递包裹
	UTSA_ItemDragDropOp* DragDropOp = NewObject<UTSA_ItemDragDropOp>(this);
	
	// 2. 填写发货单信息 (从自身获取)
	// 假设你有一个方法能拿到所在的背包组件 (比如在初始化时存进来的，或者通过 GetTypedOuter 向上找)
	DragDropOp->SourceInventory = InventoryItem.Get()->GetOwningInventoryComponent();
	DragDropOp->SourceSlotIndex = SlotIndex;
	DragDropOp->PayloadItem = InventoryItem.Get();

	// 3. 设置拖拽时的鼠标视觉效果 (DefaultDragVisual)
	// 通常我们会创建一个专门的简单 Widget (只有一张图片)，或者直接把这个 SlottedItem 自己当成拖拽影像
	
	Image_Icon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	DragDropOp->DefaultDragVisual = Image_Icon; 
	
	DragDropOp->Pivot = EDragPivot::CenterCenter; 

	// 4. 将包裹交给引擎！
	OutOperation = DragDropOp;
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
			Brush.TintColor = FLinearColor(0.f, 0.7f, 0.f, 0.5f);
			break;
		case ETSA_ItemRarity::Rare:
			Brush.TintColor = FLinearColor(0.0f, 0.0f, 0.9f, 0.5f);
			break;
		case ETSA_ItemRarity::Epic:
			Brush.TintColor = FLinearColor(0.6f, 0.0f, 1.0f, 0.5f);
			break;
		case ETSA_ItemRarity::Legendary:
			Brush.TintColor = FLinearColor(1.f, 0.5f, 0.f, 0.5f);
			break;
		case ETSA_ItemRarity::Mythic:
			Brush.TintColor = FLinearColor(0.7f, 0.f, 0.f, 0.6f);
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
