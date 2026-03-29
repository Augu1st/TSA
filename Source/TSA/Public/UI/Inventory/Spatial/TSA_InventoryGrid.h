// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/TSA_GridTypes.h"

#include "TSA_InventoryGrid.generated.h"

struct FTSA_ItemDataRow;
class UTSA_SlottedItem;
class UTSA_InventoryComponent;
class UCanvasPanel;
class UTSA_GridSlot;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual void NativeOnInitialized() override;
	
	void InitializeGrid(UTSA_InventoryComponent* InventoryComponent);
	void ConstructGrid(int32 Rows, int32 Columns,int MaxCapacity);
	void ClearGrid();
	
	UFUNCTION()
	void AddItemToIndex(UTSA_InventoryItem* Item, int32 SlotIndex);
	
	UFUNCTION()
	void UpdateItemAtIndex(UTSA_InventoryItem* Item, int32 SlotIndex);
	
	UFUNCTION()
	void RemoveItemFromIndex(UTSA_InventoryItem* Item, int32 SlotIndex);
	
	void SetSlottedItemImage(UTSA_InventoryItem* Item, UTSA_SlottedItem* SlottedItem);

	UTSA_InventoryComponent* GetOwnerComponent() const;

protected:
	void SetupSlottedItem(UTSA_InventoryItem* Item, int32 SlotIndex, UTSA_SlottedItem* SlottedItem);
	
	TWeakObjectPtr<UTSA_InventoryComponent> OwnerComponent;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;
	
	/* Grid Slots */
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory|Grid")
	float SlotSize;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory|Grid")
	float SlotPadding;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory|Grid")
	TSubclassOf<UTSA_GridSlot> GridSlotClass;
	
	UPROPERTY()
	TArray<TObjectPtr<UTSA_GridSlot>> GridSlots;  
	/* End of Grid Slots */
	
	/* Slotted Item */
	UPROPERTY()
	TMap<int32, TObjectPtr<UTSA_SlottedItem>> SlottedItems;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory|Grid")
	TSubclassOf<UTSA_SlottedItem> SlottedItemClass;
	/* End of Slotted Item */
};
