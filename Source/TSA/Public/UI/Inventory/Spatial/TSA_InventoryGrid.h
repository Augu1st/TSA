// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/TSA_GridTypes.h"

#include "TSA_InventoryGrid.generated.h"

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
	void NativeOnInitialized() override;
	
	
	ETSA_GridType GetGridType() const { return GridType; }
	
private:
	
	void ConstructGrid();
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"),  Category = "TSA|Inventory|Grid")
	ETSA_GridType GridType = ETSA_GridType::General;
	
	UPROPERTY(EditAnywhere, meta=(BindWidget))
	TObjectPtr<UCanvasPanel> CanvasPanel;
	
	/* Grid Slots */
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory|Grid")
	int32 Rows;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory|Grid")
	int32 Columns;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory|Grid")
	float SlotSize;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory|Grid")
	TSubclassOf<UTSA_GridSlot> GridSlotClass;
	
	UPROPERTY()
	TArray<TObjectPtr<UTSA_GridSlot>> GridSlots;  
	/* End of Grid Slots */
};
