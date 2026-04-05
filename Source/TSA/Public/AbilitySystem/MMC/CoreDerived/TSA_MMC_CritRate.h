// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayModMagnitudeCalculation.h"
#include "TSA_MMC_CritRate.generated.h"

/**
 * 
 */
UCLASS()
class TSA_API UTSA_MMC_CritRate : public UGameplayModMagnitudeCalculation
{
	GENERATED_BODY()
public:
	UTSA_MMC_CritRate();
	virtual float CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const override;
	
private:
	FGameplayEffectAttributeCaptureDefinition ObservationDef;
};
