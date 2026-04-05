// Dark Trace Studio Works


#include "AbilitySystem/MMC/CoreDerived/TSA_MMC_PropsUseSpeed.h"

#include "AbilitySystem/AttributeSets/TSA_CoreAttributeSet.h"

UTSA_MMC_PropsUseSpeed::UTSA_MMC_PropsUseSpeed()
{
	ReactionDef.AttributeToCapture = UTSA_CoreAttributeSet::GetReactionAttribute();
	ReactionDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	ReactionDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(ReactionDef);
}

float UTSA_MMC_PropsUseSpeed::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Reaction = 0.f;
	GetCapturedAttributeMagnitude(ReactionDef, Spec, EvaluateParameters, Reaction);
	Reaction = FMath::Clamp(Reaction, 0.f, 1000.f);
	
	if (Reaction <= 0.f) return 0.f;
	
	return Reaction/(Reaction+75.f);
}
