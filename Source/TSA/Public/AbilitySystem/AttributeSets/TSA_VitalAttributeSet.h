// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "TSA_VitalAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
	GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class TSA_API UTSA_VitalAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UTSA_VitalAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	/* Health */
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Health)
	FGameplayAttributeData Health;
	ATTRIBUTE_ACCESSORS(UTSA_VitalAttributeSet, Health)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxHealth)
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UTSA_VitalAttributeSet, MaxHealth)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_HealthRegenRate)
	FGameplayAttributeData HealthRegenRate; // 生命值回复率
	ATTRIBUTE_ACCESSORS(UTSA_VitalAttributeSet, HealthRegenRate)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_HealthConsumeRate)
	FGameplayAttributeData HealthConsumeRate; // 生命值消耗率
	ATTRIBUTE_ACCESSORS(UTSA_VitalAttributeSet, HealthConsumeRate)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_HealthNetFlow)
	FGameplayAttributeData HealthNetFlow;// 生命值变化率
	ATTRIBUTE_ACCESSORS(UTSA_VitalAttributeSet, HealthNetFlow)
	
	UFUNCTION()
	void OnRep_Health(const FGameplayAttributeData& OldHealth);
	
	UFUNCTION()
	void OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth);
	
	UFUNCTION()
	 void OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate);
	
	UFUNCTION()
	 void OnRep_HealthConsumeRate(const FGameplayAttributeData& OldHealthConsumeRate);
	
	UFUNCTION()
	 void OnRep_HealthNetFlow(const FGameplayAttributeData& OldHealthNetFlow);
	/* End of Health */
	
	/* Armor */
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_Armor)
	FGameplayAttributeData Armor;
	ATTRIBUTE_ACCESSORS(UTSA_VitalAttributeSet, Armor)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_MaxArmor)
	FGameplayAttributeData MaxArmor;
	ATTRIBUTE_ACCESSORS(UTSA_VitalAttributeSet, MaxArmor)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ArmorRegenRate)
	FGameplayAttributeData ArmorRegenRate;// 护甲回复率
	ATTRIBUTE_ACCESSORS(UTSA_VitalAttributeSet, ArmorRegenRate)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ArmorConsumeRate)
	FGameplayAttributeData ArmorConsumeRate;// 护甲消耗率
	ATTRIBUTE_ACCESSORS(UTSA_VitalAttributeSet, ArmorConsumeRate)
	
	UPROPERTY(BlueprintReadOnly,ReplicatedUsing=OnRep_ArmorNetFlow)
	FGameplayAttributeData ArmorNetFlow;// 护甲变化率
	ATTRIBUTE_ACCESSORS(UTSA_VitalAttributeSet, ArmorNetFlow)
	
	UFUNCTION()
	void OnRep_Armor(const FGameplayAttributeData& OldArmor);
	
	UFUNCTION()
	void OnRep_MaxArmor(const FGameplayAttributeData& OldMaxArmor);
	
	UFUNCTION()
	void OnRep_ArmorRegenRate(const FGameplayAttributeData& OldArmorRegenRate);
	
	UFUNCTION()
	void OnRep_ArmorConsumeRate(const FGameplayAttributeData& OldArmorConsumeRate);
	
	UFUNCTION()
	void OnRep_ArmorNetFlow(const FGameplayAttributeData& OldArmorNetFlow);
	/* End of Armor */
};

