// Dark Trace Studio Works


#include "UI/Inventory/GridSlots/TSA_GridSlot.h"

#include "Components/Image.h"
#include "Components/Overlay.h"
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

	// 5. 【核心步骤】：通知服务器进行真正的物理转移！
	// UI 的任务到此结束！UI 绝对不要自己去修改里面的图片或数据！
	// 让发起方的组件（或者玩家控制器）发一个 RPC。
	
	// 这里假设你在 InventoryComponent 里写了一个请求转移的函数 (客户端会转成 Server RPC)
	SourceComp->RequestMoveItem(SourceIndex, TargetComp, TargetIndex);

	// 返回 true 告诉引擎：“包裹我已经签收了，拖拽操作圆满结束！”
	return true; 
	
}
