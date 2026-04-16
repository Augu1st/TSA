// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_GridSlot.generated.h"

class UTSA_InventoryGrid;
class UTSA_SlottedItem;
class UTSA_InventoryItem;
class UImage;

UENUM()
enum class ETSA_GridSlotState : uint8
{
	Unoccupied,
	Occupied,
	Selected,
	Locked
};

UCLASS()
class TSA_API UTSA_GridSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitSlot(UTSA_InventoryGrid* InGrid, int32 InSlotIndex);
	
	UTSA_InventoryGrid* GetParentGrid() const { return ParentGrid.Get(); }
	
	int32 GetSlotIndex() const { return SlotIndex; }
	void SetSlotIndex(const int32 Index) { SlotIndex = Index; }
	
	ETSA_GridSlotState GetGridSlotState() const { return GridSlotState; }
	void SetGridSlotState(ETSA_GridSlotState State);
	
	void SetItemWidget(UTSA_SlottedItem* InItemWidget);
	void ClearItemWidget();
	bool IsEmpty() const { return CurrentItemWidget == nullptr; }
	
	UPROPERTY(BlueprintReadOnly)
	int32 SlotIndex;
	
protected:
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayCursorInAnimation();
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayCursorOutAnimation();
	
private:
	
	/* Widgets */
	// UMG 中用来装物品的容器
	UPROPERTY(meta=(BindWidget))
	class UOverlay* ItemContainer;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_GridSlot;
	/* End of Widgets */	
	
	TWeakObjectPtr<UTSA_InventoryGrid> ParentGrid;
	
	UPROPERTY()
	UTSA_SlottedItem* CurrentItemWidget = nullptr;
	
	UPROPERTY(EditAnywhere, Category="TSA|Inventory")
	FSlateBrush Brush_Unoccupied;
	
	UPROPERTY(EditAnywhere, Category="TSA|Inventory")
	FSlateBrush Brush_Occupied;
	
	UPROPERTY(EditAnywhere, Category="TSA|Inventory")
	FSlateBrush Brush_Selected;
	
	UPROPERTY(EditAnywhere, Category="TSA|Inventory")
	FSlateBrush Brush_Locked;
	
	ETSA_GridSlotState GridSlotState = ETSA_GridSlotState::Unoccupied;
};
