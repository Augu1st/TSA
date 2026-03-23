// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemReplicationProxyInterface.h"
#include "GameFramework/PlayerState.h"
#include "TSA_PlayerState.generated.h"

class UTSA_HealthAttributeSet;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class TSA_API ATSA_PlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()
	
public:
	ATSA_PlayerState();
	
	//~AbilitySystemComponent
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	//~End of AbilitySystemComponent

protected:
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;
	
	/* Attribute Sets*/
	UPROPERTY()
	TObjectPtr<UTSA_HealthAttributeSet> HealthSet;
	/* End of Attribute Sets*/
	
private:
	void InitASC();
	void InitAttributeSets();
};
