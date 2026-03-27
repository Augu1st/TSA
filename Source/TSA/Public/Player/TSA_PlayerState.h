// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "AbilitySystemReplicationProxyInterface.h"
#include "GameFramework/PlayerState.h"
#include "TSA_PlayerState.generated.h"

class UTSA_ResourceAttributeSet;
class UTSA_CoreAttributeSet;
class UTSA_CombatAttributeSet;
class UTSA_VitalAttributeSet;
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
	TObjectPtr<UTSA_VitalAttributeSet> HealthSet;
	
	UPROPERTY()
	TObjectPtr<UTSA_CombatAttributeSet> CombatSet;
	
	UPROPERTY()
	TObjectPtr<UTSA_CoreAttributeSet> CoreSet;
	
	UPROPERTY()
	TObjectPtr<UTSA_ResourceAttributeSet> ResourceSet;
	/* End of Attribute Sets*/
	
private:
	void InitASC();
	void InitAttributeSets();
};
