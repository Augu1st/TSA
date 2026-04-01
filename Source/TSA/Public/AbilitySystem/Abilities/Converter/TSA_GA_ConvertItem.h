// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/Base/TSA_GameplayAbility.h"
#include "TSA_GA_ConvertItem.generated.h"

/**
 * 
 */
UCLASS()
class TSA_API UTSA_GA_ConvertItem : public UTSA_GameplayAbility
{
	GENERATED_BODY()
	
public:
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	
	UPROPERTY(EditDefaultsOnly,Category="TSA|Converter")
	TSubclassOf<UGameplayEffect> ProduceEnergy;
	
	UPROPERTY(EditDefaultsOnly,Category="TSA|Converter")
	TSubclassOf<UGameplayEffect> ProduceMatter;
};
