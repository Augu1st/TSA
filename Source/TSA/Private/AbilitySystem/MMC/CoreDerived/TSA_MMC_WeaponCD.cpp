// Dark Trace Studio Works


#include "AbilitySystem/MMC/CoreDerived/TSA_MMC_WeaponCD.h"

#include "AbilitySystem/AttributeSets/TSA_CoreAttributeSet.h"

UTSA_MMC_WeaponCD::UTSA_MMC_WeaponCD()
{
	MasteryDef.AttributeToCapture = UTSA_CoreAttributeSet::GetMasteryAttribute();
	MasteryDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Target;
	MasteryDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(MasteryDef);
}

float UTSA_MMC_WeaponCD::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float Mastery = 0.f;
	GetCapturedAttributeMagnitude(MasteryDef, Spec, EvaluateParameters, Mastery);
	Mastery = FMath::Clamp(Mastery, 0.f, 1000.f);
	
	if (Mastery <= 0.f) return 0.f;
	
	float WeaponCooldown = Mastery / (Mastery + 200.f);
	return WeaponCooldown;
}
