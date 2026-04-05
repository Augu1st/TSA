// Dark Trace Studio Works


#include "AbilitySystem/MMC/CoreDerived/TSA_MMC_HealthRegenRate.h"

#include "AbilitySystem/AttributeSets/TSA_CoreAttributeSet.h"
#include "AbilitySystem/AttributeSets/TSA_VitalAttributeSet.h"

UTSA_MMC_HealthRegenRate::UTSA_MMC_HealthRegenRate()
{
	MaxHealthDef.AttributeToCapture = UTSA_VitalAttributeSet::GetMaxHealthAttribute();
	MaxHealthDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	MaxHealthDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(MaxHealthDef);
	
	TenacityDef.AttributeToCapture = UTSA_CoreAttributeSet::GetTenacityAttribute();
	TenacityDef.AttributeSource = EGameplayEffectAttributeCaptureSource::Source;
	TenacityDef.bSnapshot = false;
	RelevantAttributesToCapture.Add(TenacityDef);
}

float UTSA_MMC_HealthRegenRate::CalculateBaseMagnitude_Implementation(const FGameplayEffectSpec& Spec) const
{
	const FGameplayTagContainer* SourceTags = Spec.CapturedSourceTags.GetAggregatedTags();
	const FGameplayTagContainer* TargetTags = Spec.CapturedTargetTags.GetAggregatedTags();
	
	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = SourceTags;
	EvaluateParameters.TargetTags = TargetTags;
	
	float MaxHealth = 0.f;
	GetCapturedAttributeMagnitude(MaxHealthDef, Spec, EvaluateParameters, MaxHealth);
	MaxHealth = FMath::Max<float>(MaxHealth, 0.f);
	if (MaxHealth <= 0.f) return 0.f;
	
	float Tenacity = 0.f;
	GetCapturedAttributeMagnitude(TenacityDef, Spec, EvaluateParameters, Tenacity);
	Tenacity = FMath::Clamp(Tenacity, 0.f, 1000.f);
	if (Tenacity <= 0.f) return 0.f;
	
	float HealthRegenRate = MaxHealth * 0.05 * Tenacity/(Tenacity + 100.f);
	return HealthRegenRate;
}
