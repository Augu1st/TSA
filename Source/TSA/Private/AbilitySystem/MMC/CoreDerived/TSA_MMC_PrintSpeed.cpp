// Dark Trace Studio Works


#include "AbilitySystem/MMC/CoreDerived/TSA_MMC_PrintSpeed.h"

#include "AbilitySystem/AttributeSets/TSA_CoreAttributeSet.h"

UTSA_MMC_PrintSpeed::UTSA_MMC_PrintSpeed()
{
	CalculationDef.AttributeToCapture = UTSA_CoreAttributeSet::GetReactionAttribute();
	CalculationDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	CalculationDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(CalculationDef);
}

float UTSA_MMC_PrintSpeed::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Calculation = 0.f;
	GetCapturedAttributeMagnitude(CalculationDef, Spec, EvaluateParameters, Calculation);
	Calculation = FMath::Clamp(Calculation, 0.f, 1000.f);
	
	if (Calculation <= 0.f) return 0.f;
	
	return Calculation/(Calculation+75.f);
}
