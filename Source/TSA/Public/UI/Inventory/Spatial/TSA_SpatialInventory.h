// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "UI/Inventory/TSA_InventoryBase.h"
#include "TSA_SpatialInventory.generated.h"

class UTSA_InventoryGrid;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_SpatialInventory : public UTSA_InventoryBase
{
	GENERATED_BODY()
	
private:
	
	UPROPERTY(EditAnywhere, Category="TSA|Inventory")
	TArray<TObjectPtr<UTSA_InventoryGrid>> InventoryGrids;
};
