// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "AbilitySystemComponent.h"
#include "TSA_CombatAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class TSA_API UTSA_CombatAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
	
public:
	UTSA_CombatAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	/* Critical 暴击 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CritRate)
	FGameplayAttributeData CritRate;//暴击率
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, CritRate)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_CritDamage)
	FGameplayAttributeData CritDamage;//暴击伤害
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, CritDamage)
	
	UFUNCTION()
	void OnRep_CritRate(const FGameplayAttributeData& OldCritRate);
	
	UFUNCTION()
	void OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage);
	/* End of Critical */
	
	/* DodgeRate 闪避率 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_DodgeRate)
	FGameplayAttributeData DodgeRate;
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, DodgeRate)
	
	UFUNCTION()
	void OnRep_DodgeRate(const FGameplayAttributeData& OldDodgeRate);
	/* End of DodgeRate */
	
	/* Resist 抗性*/
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Resist_Sturdy)
	FGameplayAttributeData Resist_Sturdy;//坚固
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, Resist_Sturdy)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Resist_Toughness)
	FGameplayAttributeData Resist_Toughness;//韧性
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, Resist_Toughness)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Resist_Stable)
	FGameplayAttributeData Resist_Stable;//稳定
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, Resist_Stable)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Resist_Reflect)
	FGameplayAttributeData Resist_Reflect;//反射
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, Resist_Reflect)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Resist_Insulate_E)
	FGameplayAttributeData Resist_Insulate_E;//绝缘
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, Resist_Insulate_E)

	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Resist_Insulate_H)
	FGameplayAttributeData Resist_Insulate_H;//隔热
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, Resist_Insulate_H)
	
	UFUNCTION()
	void OnRep_Resist_Sturdy(const FGameplayAttributeData& OldResist_Sturdy);
	
	UFUNCTION()
	void OnRep_Resist_Toughness(const FGameplayAttributeData& OldResist_Toughness);
    	
	UFUNCTION()
	void OnRep_Resist_Stable(const FGameplayAttributeData& OldResist_Stable);
	
	UFUNCTION()
	void OnRep_Resist_Reflect(const FGameplayAttributeData& OldResist_Reflect);
		
	UFUNCTION()
	void OnRep_Resist_Insulate_E(const FGameplayAttributeData& OldResist_Insulate_E);
		
	UFUNCTION()
	void OnRep_Resist_Insulate_H(const FGameplayAttributeData& OldResist_Insulate_H);
	/* End of Resist */
	
};


