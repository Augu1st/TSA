// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TSA_MessageUtils.generated.h"

class UTSA_UIMessageSubsystem;

UCLASS()
class TSA_API UTSA_MessageUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "TSA|Utils")
	static UTSA_UIMessageSubsystem* GetUIMessageSubsystem(const AActor* Caller);
};
