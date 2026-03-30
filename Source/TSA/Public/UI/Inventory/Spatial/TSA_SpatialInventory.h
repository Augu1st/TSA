// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "UI/Inventory/TSA_InventoryBase.h"
#include "TSA_SpatialInventory.generated.h"

struct FGameplayTag;
class UCanvasPanel;
class UTSA_InventoryGrid;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_SpatialInventory : public UTSA_InventoryBase
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAttribute(FGameplayTag AttributeTag, float NewValue);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InventoryGrid> Grid_Equipment;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InventoryGrid> Grid_Prop;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InventoryGrid> Grid_General;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InventoryGrid> Grid_Container;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InventoryGrid> Grid_Weapon;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InventoryGrid> Grid_Armor;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InventoryGrid> Grid_Module;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InventoryGrid> Grid_Converter;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InventoryGrid> Grid_Printer;
};
