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
	
	/* Cooldown 冷却 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_WeaponCooldown)
	FGameplayAttributeData WeaponCooldown;// 武器冷却
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, WeaponCooldown)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ModuleCooldown)
	FGameplayAttributeData ModuleCooldown;// 模块冷却
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, ModuleCooldown)
	
	UFUNCTION()
	void OnRep_WeaponCooldown(const FGameplayAttributeData& OldWeaponCooldown);
	
	UFUNCTION()
	void OnRep_ModuleCooldown(const FGameplayAttributeData& OldModuleCooldown);
	/* End of Cooldown */
	
	/* Prop 道具 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PropUseSpeed)
	FGameplayAttributeData PropUseSpeed;//道具使用速度
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, PropUseSpeed)
	
	UFUNCTION()
	void OnRep_PropUseSpeed(const FGameplayAttributeData& OldPropUseSpeed);
	/* End of Prop */
	
	/* Speed 速度 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MovementSpeed)
	FGameplayAttributeData MovementSpeed;// 移动速度
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, MovementSpeed)
	
	UFUNCTION()
	void OnRep_MovementSpeed(const FGameplayAttributeData& OldMovementSpeed);
	/* End of Speed */
	
	/* Resist 抗性 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PhysicalResistance)
	FGameplayAttributeData PhysicalResistance; // 物理抗性
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, PhysicalResistance)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_EnergyResistance)
	FGameplayAttributeData EnergyResistance; // 能量抗性
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, EnergyResistance)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_StructureResistance)
	FGameplayAttributeData StructureResistance; // 结构抗性
	ATTRIBUTE_ACCESSORS(UTSA_CombatAttributeSet, StructureResistance)
	
	UFUNCTION()
	void OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance);
	
	UFUNCTION()
	void OnRep_EnergyResistance(const FGameplayAttributeData& OldEnergyResistance);
	
	UFUNCTION()
	void OnRep_StructureResistance(const FGameplayAttributeData& OldStructureResistance);
	/* End of Resist */
	
};


