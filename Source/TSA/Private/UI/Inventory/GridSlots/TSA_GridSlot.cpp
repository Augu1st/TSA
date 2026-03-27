// Dark Trace Studio Works


#include "UI/Inventory/GridSlots/TSA_GridSlot.h"

#include "Components/Image.h"
#include "Components/Overlay.h"
#include "Player/TSA_PlayerController.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "UI/Inventory/SlottedItems/TSA_ItemDragDropOp.h"
#include "UI/Inventory/SlottedItems/TSA_SlottedItem.h"
#include "UI/Inventory/Spatial/TSA_InventoryGrid.h"


void UTSA_GridSlot::InitSlot(UTSA_InventoryGrid* InGrid, int32 InSlotIndex)
{
	ParentGrid = InGrid;
	SlotIndex = InSlotIndex;
}

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

void UTSA_GridSlot::SetItemWidget(UTSA_SlottedItem* InItemWidget)
{
	CurrentItemWidget = InItemWidget;
	if (CurrentItemWidget && ItemContainer)
	{
		// 将物品 UI 作为子控件塞进格子里
		ItemContainer->AddChild(CurrentItemWidget);
		SetGridSlotState(ETSA_GridSlotState::Occupied);
	}
}

void UTSA_GridSlot::ClearItemWidget()
{
	if (CurrentItemWidget)
	{
		CurrentItemWidget->RemoveFromParent();
		CurrentItemWidget = nullptr;
	}
	SetGridSlotState(ETSA_GridSlotState::Unoccupied);
}

void UTSA_GridSlot::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
	PlayCursorInAnimation();
}

void UTSA_GridSlot::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	
	PlayCursorOutAnimation();
}

void UTSA_GridSlot::NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,UDragDropOperation* InOperation)
{
	Super::NativeOnDragEnter(InGeometry, InDragDropEvent, InOperation);
	
	PlayCursorInAnimation();
}

void UTSA_GridSlot::NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation)
{
	Super::NativeOnDragLeave(InDragDropEvent, InOperation);
	
	PlayCursorOutAnimation();
}

bool UTSA_GridSlot::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,UDragDropOperation* InOperation)
{
	// 1. 检查扔下来的包裹是不是我们的“物品快递”
	UTSA_ItemDragDropOp* ItemDropOp = Cast<UTSA_ItemDragDropOp>(InOperation);
	if (!ItemDropOp)
	{
		// 如果扔的是别的东西（比如拖了张无关的图片过来），我不处理。交回给父类。
		return Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	}

	// 2. 提取“发货单”信息
	UTSA_InventoryComponent* SourceComp = ItemDropOp->SourceInventory.Get();
	int32 SourceIndex = ItemDropOp->SourceSlotIndex;

	// 3. 获取“收货地”信息 (我自己的地址)
	// 假设你能拿到自己所在的背包组件
	UTSA_InventoryComponent* TargetComp = ParentGrid->GetOwnerComponent();
	int32 TargetIndex = SlotIndex;

	// 4. 基本的安全拦截 (UI 层的防御，避免无意义的网络请求)
	// 如果源和目标是同一个背包的同一个格子，也就是拿起来又原地放下，直接取消。
	if (SourceComp == TargetComp && SourceIndex == TargetIndex)
	{
		return true;
	}

	// 如果其中一个组件为空，说明出了 bug，取消
	if (!SourceComp || !TargetComp)
	{
		return false; 
	}

	// 5. 【核心步骤】：通知服务器进行真正的物理转移
	ATSA_PlayerController* PC = Cast<ATSA_PlayerController>(GetOwningPlayer());
	if (PC)
	{
		// 委托拥有网络权限的 Controller 去发 RPC
		PC->RequestMoveItem(SourceComp, SourceIndex, TargetComp, TargetIndex);
	}
	
	return true; 
}
