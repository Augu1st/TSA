// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TSA_ItemUtils.generated.h"

struct FInstancedStruct;
struct FGameplayTag;
struct FTSA_ItemManifestBase;
class UTSA_InventoryItem;
class UTSA_ItemComponent;
struct FTSA_ItemDataRow;

/**
 * 
 */
UCLASS()
class TSA_API UTSA_ItemUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintPure, Category = "TSA|Item")
	static bool GetItemStaticDataFromItemComp(UTSA_ItemComponent* ItemComponent, FTSA_ItemDataRow& OutItemData);
	
	UFUNCTION(BlueprintPure, Category = "TSA|Item")
	static bool GetItemStaticDataFromItem(UTSA_InventoryItem* Item, FTSA_ItemDataRow& OutItemData);
	
	UFUNCTION(BlueprintPure, Category = "TSA|Item")
	static bool GetItemStaticDataFromManifestStruct(const FInstancedStruct& ItemManifestStruct, FTSA_ItemDataRow& OutItemData);
	
	UFUNCTION(BlueprintPure, Category = "TSA|Item")
	static FGameplayTag GetItemCategoryFromManifest(const FTSA_ItemManifestBase& Manifest);
	
	UFUNCTION(BlueprintPure, Category = "TSA|Item")
	static FGameplayTag GetItemCategoryFromItem(UTSA_InventoryItem* Item);
    	
	UFUNCTION(BlueprintPure, Category = "TSA|Item")
	static FGameplayTag GetItemCategoryFromItemComp(UTSA_ItemComponent* ItemComponent);
	
	UFUNCTION(BlueprintPure, Category = "TSA|Item")
	static bool GetItemDataFromManifest(const FTSA_ItemManifestBase& Manifest, FTSA_ItemDataRow& OutItemData);
};