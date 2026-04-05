// Dark Trace Studio Works


#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"

#include "AbilitySystem/AttributeSets/TSA_ResourceAttributeSet.h"
#include "AbilitySystem/AttributeSets/TSA_VitalAttributeSet.h"


bool UTSA_AbilitySystemComponent::IsHealthFull() const
{
	float CurrentHealth = GetNumericAttribute(UTSA_VitalAttributeSet::GetHealthAttribute());
	float MaxHealth = GetNumericAttribute(UTSA_VitalAttributeSet::GetMaxHealthAttribute());
	return FMath::IsNearlyEqual(CurrentHealth, MaxHealth);
}

bool UTSA_AbilitySystemComponent::IsArmorFull() const
{
	float CurrentArmor = GetNumericAttribute(UTSA_VitalAttributeSet::GetArmorAttribute());
	float MaxArmor = GetNumericAttribute(UTSA_VitalAttributeSet::GetMaxArmorAttribute());
	return FMath::IsNearlyEqual(CurrentArmor, MaxArmor);
}

bool UTSA_AbilitySystemComponent::IsEnergyFull() const
{
	float CurrentEnergy = GetNumericAttribute(UTSA_ResourceAttributeSet::GetEnergyAttribute());
	float MaxEnergy = GetNumericAttribute(UTSA_ResourceAttributeSet::GetMaxEnergyAttribute());
	return FMath::IsNearlyEqual(CurrentEnergy, MaxEnergy);
}

bool UTSA_AbilitySystemComponent::IsMatterFull() const
{
	float CurrentMatter = GetNumericAttribute(UTSA_ResourceAttributeSet::GetMatterAttribute());
	float MaxMatter = GetNumericAttribute(UTSA_ResourceAttributeSet::GetMaxMatterAttribute());
	return FMath::IsNearlyEqual(CurrentMatter, MaxMatter);
}

void UTSA_AbilitySystemComponent::GiveAbilityWithClassesAndLevel(
	const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses, int32 Level)
{
	for (const auto& AbilityClass : AbilityClasses)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, Level);
		GiveAbility(AbilitySpec);
	}
}

