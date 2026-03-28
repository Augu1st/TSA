// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "TSA_CharacterBase.generated.h"

class UGameplayEffect;
class UTSA_CombatAttributeSet;
class UTSA_VitalAttributeSet;
class UAbilitySystemComponent;

UCLASS()
class TSA_API ATSA_CharacterBase : public ACharacter,public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	ATSA_CharacterBase();
	//~AbilitySystemComponent
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End of AbilitySystemComponent
protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	/* Attribute Sets */
	UPROPERTY()
	TObjectPtr<UTSA_VitalAttributeSet> VitalSet;
	
	UPROPERTY()
	TObjectPtr<UTSA_CombatAttributeSet> CombatSet;
	/* End of Attribute Sets */
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayEffect>> InitAttributeGEClasses;
};
