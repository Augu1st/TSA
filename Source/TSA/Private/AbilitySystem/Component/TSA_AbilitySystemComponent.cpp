// Dark Trace Studio Works


#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"


void UTSA_AbilitySystemComponent::GiveAbilityWithClassesAndLevel(
	const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses, int32 Level)
{
	for (const auto& AbilityClass : AbilityClasses)
	{
		FGameplayAbilitySpec AbilitySpec = FGameplayAbilitySpec(AbilityClass, Level);
		GiveAbility(AbilitySpec);
	}
}

