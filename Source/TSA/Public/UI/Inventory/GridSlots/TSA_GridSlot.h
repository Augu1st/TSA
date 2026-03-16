// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_GridSlot.generated.h"

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
	int32 GetSlotIndex() const { return SlotIndex; }
	void SetSlotIndex(const int32 Index) { SlotIndex = Index; }
	
	ETSA_GridSlotState GetGridSlotState() const { return GridSlotState; }
	void SetGridSlotState(ETSA_GridSlotState State);
	
private:
	
	int32 SlotIndex;
	
	/* Widgets */
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_GridSlot;
	/* End of Widgets */
	
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
