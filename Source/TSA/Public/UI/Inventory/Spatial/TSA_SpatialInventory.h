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
	
public:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InventoryGrid> Grid_Equipment;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InventoryGrid> Grid_Prop;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InventoryGrid> Grid_General;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InventoryGrid> Grid_Container;
};
