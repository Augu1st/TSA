// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_SlottedItem.generated.h"

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
	/*virtual FReply NativeOnMouseButtonDown(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void NativeOnMouseEnter(const FGeometry& MyGeometry, const FPointerEvent& MouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& MouseEvent) override;*/
	
	bool IsStackable() const { return bIsStackable; }
	void SetIsStackable(bool bStackable) { bIsStackable = bStackable; }
	
	UImage* GetImageIcon() const { return Image_Icon; }
	void SetImageBrush(const FSlateBrush& Brush) const;
	
	void SetSlotIndex(int32 Index) { SlotIndex = Index; }
	int32 GetSlotIndex() const { return SlotIndex; }
	
	void SetInventoryItem(UTSA_InventoryItem* Item);
	UTSA_InventoryItem* GetInventoryItem() const { return InventoryItem.Get(); }
	
	void UpdateStackCount(int32 StackCount);

private:

	void SetBackgroundByRarity(ETSA_ItemRarity Rarity);
	
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
};
