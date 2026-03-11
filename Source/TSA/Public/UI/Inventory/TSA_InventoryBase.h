// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/TSA_GridTypes.h"
#include "TSA_InventoryBase.generated.h"

class UTSA_ItemComponent;

UCLASS()
class TSA_API UTSA_InventoryBase : public UUserWidget
{
	GENERATED_BODY()
	
public:
	virtual FTSA_SlotAvailabilityResult HasRoomForItem(UTSA_ItemComponent* ItemComponent) const { return FTSA_SlotAvailabilityResult(); }
}; 
