// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/TSA_GridTypes.h"

#include "TSA_InventoryGrid.generated.h"

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
	
	UFUNCTION()
	void AddItem(UTSA_InventoryItem* Item);
	
	void InitializeGrid(UTSA_InventoryComponent* InventoryComponent);
	void ConstructGrid(int32 Rows, int32 Columns);
	
private:
	
	// Utils
	TWeakObjectPtr<UTSA_InventoryComponent> OwnerComponent;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;
	
	/* Grid Slots */
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory|Grid")
	float SlotSize;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory|Grid")
	TSubclassOf<UTSA_GridSlot> GridSlotClass;
	
	UPROPERTY()
	TArray<TObjectPtr<UTSA_GridSlot>> GridSlots;  
	/* End of Grid Slots */
};
