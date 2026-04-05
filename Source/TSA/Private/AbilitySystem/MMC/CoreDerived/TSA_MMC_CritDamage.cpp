// Dark Trace Studio Works


#include "AbilitySystem/MMC/CoreDerived/TSA_MMC_CritDamage.h"

#include "AbilitySystem/AttributeSets/TSA_CoreAttributeSet.h"

UTSA_MMC_CritDamage::UTSA_MMC_CritDamage()
{
	ObservationDef.AttributeToCapture = UTSA_CoreAttributeSet::GetObservationAttribute();
	ObservationDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ObservationDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(ObservationDef);
}

float UTSA_MMC_CritDamage::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Observation = 0.f;
	GetCapturedAttributeMagnitude(ObservationDef, Spec, EvaluateParameters, Observation);
	Observation = FMath::Clamp(Observation, 0.f, 1000.f);
	
	if (Observation <= 0.f) return 0.f;
	
	float CritDamage = Observation / (Observation+150.f);
	return  CritDamage;
}
