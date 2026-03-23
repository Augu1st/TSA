// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "TSA_CharacterBase.generated.h"

class UTSA_HealthAttributeSet;
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
	TObjectPtr<UTSA_HealthAttributeSet> HealthSet;
	
	/* End of Attribute Sets */
};
