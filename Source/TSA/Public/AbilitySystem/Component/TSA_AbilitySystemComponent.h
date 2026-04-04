// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "TSA_AbilitySystemComponent.generated.h"

/**
 * 
 */
UCLASS()
class TSA_API UTSA_AbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()
	
public:
	
	
	void GiveAbilityWithClassesAndLevel(const TArray<TSubclassOf<UGameplayAbility>>& AbilityClasses, int32 Level);
};
