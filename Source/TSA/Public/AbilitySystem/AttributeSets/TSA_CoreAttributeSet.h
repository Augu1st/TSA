// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "TSA_CoreAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class TSA_API UTSA_CoreAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UTSA_CoreAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	/* Mastery 掌控 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Mastery)
	FGameplayAttributeData Mastery;
	ATTRIBUTE_ACCESSORS(UTSA_CoreAttributeSet, Mastery)
	
	UFUNCTION()
	void OnRep_Mastery(const FGameplayAttributeData& OldMastery);
	/* End of Mastery */
	
	/* Reaction 反应 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Reaction)
	FGameplayAttributeData Reaction;
	ATTRIBUTE_ACCESSORS(UTSA_CoreAttributeSet, Reaction)
	
	UFUNCTION()
	void OnRep_Reaction(const FGameplayAttributeData& OldReaction);
	/* End of Reaction */
	
	/* Calculation 计算 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Calculation)
	FGameplayAttributeData Calculation;
	ATTRIBUTE_ACCESSORS(UTSA_CoreAttributeSet, Calculation)
	
	UFUNCTION()
	void OnRep_Calculation(const FGameplayAttributeData& OldCalculation);
	/* End of Calculation */
	
	/* Observation 观察 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Observation)
	FGameplayAttributeData Observation;
	ATTRIBUTE_ACCESSORS(UTSA_CoreAttributeSet, Observation)
	
	UFUNCTION()
	void OnRep_Observation(const FGameplayAttributeData& OldObservation);
	/* End of Observation */
	
	/* Tenacity 坚韧 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Tenacity)
	FGameplayAttributeData Tenacity;
	ATTRIBUTE_ACCESSORS(UTSA_CoreAttributeSet, Tenacity)
	
	UFUNCTION()
	void OnRep_Tenacity(const FGameplayAttributeData& OldTenacity);
	/* End of Tenacity */
	
	/* Resonance 共感 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Resonance)
	FGameplayAttributeData Resonance;
	ATTRIBUTE_ACCESSORS(UTSA_CoreAttributeSet, Resonance)
	
	UFUNCTION()
	void OnRep_Resonance(const FGameplayAttributeData& OldResonance);
	/* End of Resonance */
};
