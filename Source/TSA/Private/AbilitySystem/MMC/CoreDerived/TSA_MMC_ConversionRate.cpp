// Dark Trace Studio Works


#include "AbilitySystem/MMC/CoreDerived/TSA_MMC_ConversionRate.h"

#include "AbilitySystem/AttributeSets/TSA_CoreAttributeSet.h"

UTSA_MMC_ConversionRate::UTSA_MMC_ConversionRate()
{
	ResonanceDef.AttributeToCapture = UTSA_CoreAttributeSet::GetResonanceAttribute();
	ResonanceDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	ResonanceDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(ResonanceDef);
}

float UTSA_MMC_ConversionRate::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Resonance = 0.f;
	GetCapturedAttributeMagnitude(ResonanceDef, Spec, EvaluateParameters, Resonance);
	Resonance = FMath::Clamp(Resonance, 0.f, 1000.f);
	
	if (Resonance <= 0.f) return 0.f;
	return 0.25 * Resonance / (Resonance + 100.f);
}
