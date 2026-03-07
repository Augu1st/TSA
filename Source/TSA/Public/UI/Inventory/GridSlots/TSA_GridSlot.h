// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_GridSlot.generated.h"

class UImage;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_GridSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	int32 GetSlotIndex() const { return SlotIndex; }
	void SetSlotIndex(const int32 Index) { SlotIndex = Index; }
	
private:
	
	int32 SlotIndex;
	
	/* Widgets */
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_GridSlot;
	/* End of Widgets */
};
