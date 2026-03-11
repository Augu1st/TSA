// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TSA_InventoryStatics.generated.h"

class UTSA_InventoryComponent;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_InventoryStatics : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable, Category = "TSA|Inventory")
	static  UTSA_InventoryComponent* GetInventoryComponent(AActor* Actor);
};
