// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TSA_CommonLibrary.generated.h"

class UTSA_UIMessageSubsystem;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_CommonLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "TSA|Utils")
	static TArray<AActor*> FindInteractableActorsInRange(const AActor* Caller, const float& Range,const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes,const TArray<AActor*>& IgnoreActors);
	
	UFUNCTION(BlueprintCallable, Category = "TSA|Utils")
	static FVector GetRandomLocationAtPlayerFoot(const AActor* PlayerActor, float TraceDistance, float Radius);
	
	UFUNCTION(BlueprintCallable, Category = "TSA|Utils")
	static float GetConversionRatio(UObject* WorldContextObject);
};
