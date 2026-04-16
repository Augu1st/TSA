// Dark Trace Studio Works


#include "UI/Inventory/SlottedItems/TSA_SlottedItem.h"

#include "TSA_GameplayTags.h"
#include "Types/TSA_ItemTypes.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Components/Image.h"
#include "Components/PanelWidget.h"
#include "Components/TextBlock.h"
#include "GameFramework/Character.h"
#include "Items/TSA_InventoryItem.h"
#include "Items/DataAssets/TSA_ItemDataAsset.h"
#include "Items/DataAssets/TSA_ItemFragment.h"
#include "Player/TSA_PlayerController.h"
#include "UI/Inventory/SlottedItems/TSA_ItemDragDropOp.h"
#include "Utils/TSA_ItemUtils.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "UI/HUD/TSA_HUD.h"
#include "UI/Inventory/SlottedItems/TSA_ContextMenu.h"
#include "UI/Inventory/SlottedItems/TSA_ItemDetailsWidget.h"
#include "Utils/TSA_WidgetUtils.h"


void UTSA_SlottedItem::SetImageBrush(const FSlateBrush& Brush) const
{
	Image_Icon->SetBrush(Brush);
}

void UTSA_SlottedItem::SetInventoryItem(UTSA_InventoryItem* Item)
{
	InventoryItem = Item;
	Item->SlottedItem = this;
	FTSA_ItemDataRow ItemDataRow;
	UTSA_ItemUtils::GetItemStaticDataFromItem(Item, ItemDataRow);
	const FInstancedStruct& ItemManifestStruct = Item->GetItemManifestStruct();
	
	// 设置背景
	ETSA_ItemRarity Rarity = ItemDataRow.Rarity;
	SetBackgroundByRarity(Rarity);
	
	// 设置堆叠数量
	bIsStackable = ItemDataRow.bStackable;
	if (bIsStackable)
	{	
		MaxStackCount = ItemDataRow.MaxStackCount;
		UpdateStackCount(ItemManifestStruct.Get<FTSA_ItemManifest>().StackCount);
		Text_StackCount->SetVisibility(ESlateVisibility::Visible);
	}
	else
	{
		Text_StackCount->SetVisibility(ESlateVisibility::Collapsed);
	}
	
	// 创建物品详情
	if (ItemDetailsWidgetClass && !ItemDetailsWidget)
	{
		ItemDetailsWidget = CreateWidget<UTSA_ItemDetailsWidget>(GetOwningPlayer(), ItemDetailsWidgetClass);
	}
	
}

void UTSA_SlottedItem::UpdateStackCount(int32 StackCount)
{
	if (!bIsStackable) return;
	Text_StackCount->SetText(FText::FromString(FString::FromInt(StackCount)+ "/" + FString::FromInt(MaxStackCount)));
}

FReply UTSA_SlottedItem::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	SetToolTip(nullptr);
	// 响应左键拖拽
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		// 如果左键按住并且鼠标发生了位移，请调用 NativeOnDragDetected
		return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton).NativeReply;
	}
	// 响应右键
	if (InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton)
	{
		ATSA_HUD* HUD = Cast<ATSA_HUD>(GetOwningPlayer()->GetHUD());
		if (!HUD) return FReply::Handled();
		if (HUD->GetContextMenu()) HUD->GetContextMenu()->CloseMenu();
		CreateAndShowContextMenu(InMouseEvent);
	}
	return Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
}

void UTSA_SlottedItem::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	
	if (!InventoryItem.IsValid()) return;
	// 1. 创建我们的专属快递包裹
	UTSA_ItemDragDropOp* DragDropOp = NewObject<UTSA_ItemDragDropOp>(this);
	
	// 2. 填写发货单信息 (从自身获取)
	DragDropOp->SourceInventory = GetOwningInventoryComponent();
	DragDropOp->SourceSlotIndex = SlotIndex;
	DragDropOp->PayloadItem = InventoryItem.Get();

	// 3. 设置拖拽时的鼠标视觉效果 (DefaultDragVisual)
	Image_Icon->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	DragDropOp->DefaultDragVisual = Image_Icon; 
	DragDropOp->DefaultDragVisual->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
	
	DragDropOp->Pivot = EDragPivot::CenterCenter; 

	// 4. 将包裹交给引擎！
	OutOperation = DragDropOp;
}

FReply UTSA_SlottedItem::NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	if (InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton)
	{
		if (UTSA_InventoryComponent* Inventory = GetOwningInventoryComponent())
		{
			ATSA_AgentCharacter* Agent = Cast<ATSA_AgentCharacter>(GetOwningPlayer()->GetPawn());
			if (Inventory == Agent->GetInventoryCompByCategory(ItemTags::Category::Equipment) ||
				Inventory == Agent->GetInventoryCompByCategory(ItemTags::Category::Prop) || 
				Inventory == Agent->GetInventoryCompByCategory(ItemTags::Category::General))
			{
				return FReply::Handled();
			}
			
			ATSA_PlayerController* PlayerController = Cast<ATSA_PlayerController>(GetWorld()->GetFirstPlayerController());
			PlayerController->RequestAutoAddItem(Inventory,SlotIndex);
		}
	}
	return FReply::Handled();
}

void UTSA_SlottedItem::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
	GetWorld()->GetTimerManager().SetTimer(ItemDetailsTimerHandle, this, &UTSA_SlottedItem::ShowItemDetails, ItemDetailsDelay, false);
	
	PlayCursorInAnimation();
}

void UTSA_SlottedItem::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	
	// 取消显示物品详情
	GetWorld()->GetTimerManager().ClearTimer(ItemDetailsTimerHandle);
	SetToolTip(nullptr);
	if (ItemDetailsWidget)
	{
		ItemDetailsWidget->ClearRichText();
	}
	
	PlayCursorOutAnimation();
}

void UTSA_SlottedItem::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
	
	PlayCursorInAnimation();
}

void UTSA_SlottedItem::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	
	PlayCursorOutAnimation();
}

void UTSA_SlottedItem::ShowItemDetails()
{
	if (ItemDetailsWidget)
	{
		if (!InventoryItem.IsValid()) return;
		const FInstancedStruct& ItemManifestStruct = InventoryItem.Get()->GetItemManifestStruct();
		if (ItemDetailsWidget) ItemDetailsWidget->SetUpItemDetails(ItemManifestStruct);
		SetToolTip(ItemDetailsWidget);
	}
}

void UTSA_SlottedItem::CreateAndShowContextMenu(const FPointerEvent& InMouseEvent)
{
	if (!InventoryItem.IsValid()) return;
	ATSA_HUD* HUD = Cast<ATSA_HUD>(GetOwningPlayer()->GetHUD());
	if (!HUD) return;
	
	UTSA_ContextMenu* ContextMenu = CreateWidget<UTSA_ContextMenu>(GetOwningPlayer(), HUD->GetContextMenuClass());
	
	UTSA_ItemDataAsset* ItemAsset = UTSA_ItemUtils::GetItemDataAssetFromItem(InventoryItem.Get());
	if (ItemAsset)
	{
		if (ItemAsset->FindFragment<UTSA_EquipStatFragment>())
		{
			FOnContextActionClicked Action;
			Action.BindDynamic(this, &UTSA_SlottedItem::ExecuteEquip);
			ContextMenu->AddMenuOption(FText::FromString(TEXT("装备")), Action);
		}
		
		if (ItemAsset->FindFragment<UTSA_PropFragment>())
		{
			FOnContextActionClicked Action;
			Action.BindDynamic(this, &UTSA_SlottedItem::ExecuteUseProp);
			ContextMenu->AddMenuOption(FText::FromString(TEXT("使用")), Action);
		}
	}
	FOnContextActionClicked DropAction;
	DropAction.BindDynamic(this, &UTSA_SlottedItem::ExecuteDropItem);
	ContextMenu->AddMenuOption(FText::FromString(TEXT("丢弃")), DropAction);
	
	FVector2D ViewportPos = UTSA_WidgetUtils::GetViewportPositionFromMouseEvent(this, InMouseEvent);
	ContextMenu->SetMenuPosition(ViewportPos);
	ContextMenu->AddToViewport(2);
	
	HUD->SetContextMenu(ContextMenu);
}

void UTSA_SlottedItem::ExecuteUseProp()
{
	UTSA_InventoryComponent* Inventory = GetOwningInventoryComponent();
	if (Inventory)
	{
		Inventory->UseProp(InventoryItem.Get(), SlotIndex);
	}
}

void UTSA_SlottedItem::ExecuteDropItem()
{
	UTSA_InventoryComponent* Inventory = GetOwningInventoryComponent();
	if (Inventory)
	{
		Inventory->DropItemIntoWorld(SlotIndex);
	}
}

void UTSA_SlottedItem::ExecuteEquip()
{
	if (UTSA_InventoryComponent* Inventory = GetOwningInventoryComponent())
	{
		Inventory->EquipItem(InventoryItem.Get(), SlotIndex);
	}
}

void UTSA_SlottedItem::SetBackgroundByRarity(ETSA_ItemRarity Rarity)
{
	FSlateBrush Brush = Brush_Background;
	// TODO: 修改稀有度背景显示逻辑
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
			break;
		case ETSA_ItemRarity::Destruction:
			Brush.TintColor = FLinearColor(0.0f, 0.0f, 0.0f, 0.4f);
			break;
		default:
			break;
	}
	Image_Background->SetBrush(Brush);
}

UTSA_InventoryComponent* UTSA_SlottedItem::GetOwningInventoryComponent() const
{
	if (!InventoryItem.IsValid()) return nullptr;
	return InventoryItem.Get()->GetOwningInventoryComponent();
}
