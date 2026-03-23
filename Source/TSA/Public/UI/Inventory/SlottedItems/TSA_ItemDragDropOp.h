// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "TSA_ItemDragDropOp.generated.h"

class UTSA_InventoryComponent;
class UTSA_InventoryItem;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_ItemDragDropOp : public UDragDropOperation
{
	GENERATED_BODY()
	
public:
	// “发货地”的背包组件
	UPROPERTY(BlueprintReadOnly, Category = "DragDrop")
	TWeakObjectPtr<UTSA_InventoryComponent> SourceInventory;

	// “发货地”的格子索引
	UPROPERTY(BlueprintReadOnly, Category = "DragDrop")
	int32 SourceSlotIndex = -1;

	// 被拖拽的物品数据 (用于显示或快速获取信息)
	UPROPERTY(BlueprintReadOnly, Category = "DragDrop")
	TWeakObjectPtr<UTSA_InventoryItem> PayloadItem;
	
protected:
	virtual void DragCancelled_Implementation(const FPointerEvent& PointerEvent) override;
};
