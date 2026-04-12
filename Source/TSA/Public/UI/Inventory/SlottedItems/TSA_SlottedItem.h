// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_SlottedItem.generated.h"

class UTSA_ContextMenu;
class UTSA_ItemDetailsWidget;
class UTSA_InventoryComponent;
enum class ETSA_ItemRarity : uint8;
class UTSA_InventoryItem;
class UImage;
class UTextBlock;

/**
 * 
 */
UCLASS()
class TSA_API UTSA_SlottedItem : public UUserWidget
{
	GENERATED_BODY()
	
public:
	bool IsStackable() const { return bIsStackable; }
	void SetIsStackable(bool bStackable) { bIsStackable = bStackable; }
	
	UImage* GetImageIcon() const { return Image_Icon; }
	void SetImageBrush(const FSlateBrush& Brush) const;
	
	void SetSlotIndex(int32 Index) { SlotIndex = Index; }
	int32 GetSlotIndex() const { return SlotIndex; }
	
	void SetInventoryItem(UTSA_InventoryItem* Item);
	UTSA_InventoryItem* GetInventoryItem() const { return InventoryItem.Get(); }
	
	void UpdateStackCount(int32 StackCount);

protected:
	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	// 当鼠标开始拖动时，创建包裹并返回。
	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;
	virtual FReply NativeOnMouseButtonDoubleClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnDragEnter(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	virtual void NativeOnDragLeave(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayCursorInAnimation();
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayCursorOutAnimation();
	
	void ShowItemDetails();
	
	void CreateAndShowContextMenu(const FPointerEvent& InMouseEvent);

	UFUNCTION()
	void ExecuteUseProp();
	UFUNCTION()
	void ExecuteDropItem();
	UFUNCTION()
	void ExecuteEquip();
private:
	void SetBackgroundByRarity(ETSA_ItemRarity Rarity);
	UTSA_InventoryComponent* GetOwningInventoryComponent() const;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Icon;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Background;

	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_StackCount;
	
	UPROPERTY(EditAnywhere, Category="TSA|Slot")
	FSlateBrush Brush_Background;
	
	UPROPERTY(EditAnywhere, Category="TSA|Slot")
	FSlateBrush Brush_Colorful;

	TWeakObjectPtr<UTSA_InventoryItem> InventoryItem;
	int32 SlotIndex;
	bool bIsStackable{false};
	int32 MaxStackCount = 1;
	
	/* Item Details */
	UPROPERTY(EditAnywhere, Category="TSA|Item Details")
	TSubclassOf<UUserWidget> ItemDetailsWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_ItemDetailsWidget> ItemDetailsWidget;
	
	UPROPERTY(EditAnywhere, Category="TSA|Item Details")
	float ItemDetailsDelay = 0.5f;
	
	FTimerHandle ItemDetailsTimerHandle;
	/* End of Item Details*/
	
	/* Context Menu */
	UPROPERTY(EditAnywhere, Category="TSA|Context Menu")
	TSubclassOf<UTSA_ContextMenu> ContextMenuClass;
};
