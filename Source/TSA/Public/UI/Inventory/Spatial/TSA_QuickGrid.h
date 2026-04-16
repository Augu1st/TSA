// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_QuickGrid.generated.h"

class UTSA_InventoryComponent;
class UHorizontalBox;
class UOverlay;
class UTSA_QuickSlot;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_QuickGrid : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitQuickGrid(UTSA_InventoryComponent* InventoryComponent,int32 InMaxCapacity);
	
	void ConstructGrid(int32 SlotCount);
	
private:
	
	TWeakObjectPtr<UTSA_InventoryComponent> BindComponent;
	
	/* Quick Grid */
	UPROPERTY(EditAnywhere, Category = "TSA|QuickGrid")
	FText GridName;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UOverlay> Overlay;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UHorizontalBox> HBox_Slots;
	/* End of Quick Grid */
	
	/* Quick Slot */
	UPROPERTY(EditAnywhere, Category = "TSA|QuickGrid")
	TSubclassOf<UTSA_QuickSlot> QuickSlotClass;
	
	UPROPERTY()
	TArray<TObjectPtr<UTSA_QuickSlot>> QuickSlots;
	
	UPROPERTY()
	int32 MaxCapacity = 0;
	/* End of Quick Slot */
};
