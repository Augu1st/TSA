// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "TSA_HealthAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class TSA_API UTSA_HealthAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UTSA_HealthAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	/* Health */
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTSA_HealthAttributeSet, Health)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTSA_HealthAttributeSet, MaxHealth)
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	/* End of Health */
};

