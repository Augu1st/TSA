// Dark Trace Studio Works


#include "AbilitySystem/AttributeSets/TSA_CombatAttributeSet.h"

#include "Net/UnrealNetwork.h"

UTSA_CombatAttributeSet::UTSA_CombatAttributeSet()
{
	InitCritDamage(1.25f);
	InitCritRate(0.f);
	
	InitWeaponCooldown(0.f);
	InitWeaponCooldown(0.f);
	
	InitPropUseSpeed(1.f);
	InitWalkSpeed(100.f);
	InitRunSpeed(450.f);
	InitSprintSpeed(600.f);
	
	InitPhysicalResistance(10.f);
	InitEnergyResistance(10.f);
	InitStructureResistance(0.f);
}

void UTSA_CombatAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, CritRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, CritDamage, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, WeaponCooldown, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, ModuleCooldown, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, PropUseSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, WalkSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, RunSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, SprintSpeed, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, PhysicalResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, EnergyResistance, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, StructureResistance, COND_None, REPNOTIFY_Always);
}

void UTSA_CombatAttributeSet::OnRep_CritRate(const FGameplayAttributeData& OldCritRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, CritRate, OldCritRate);
}

void UTSA_CombatAttributeSet::OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, CritDamage, OldCritDamage);
}

void UTSA_CombatAttributeSet::OnRep_WeaponCooldown(const FGameplayAttributeData& OldWeaponCooldown)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, WeaponCooldown, OldWeaponCooldown);
}

void UTSA_CombatAttributeSet::OnRep_Speed_Walk(const FGameplayAttributeData& OldSpeed_Walk)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, WalkSpeed, OldSpeed_Walk);
}

void UTSA_CombatAttributeSet::OnRep_Speed_Run(const FGameplayAttributeData& OldSpeed_Run)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, RunSpeed, OldSpeed_Run);
}

void UTSA_CombatAttributeSet::OnRep_Speed_Sprint(const FGameplayAttributeData& OldSpeed_Sprint)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, SprintSpeed, OldSpeed_Sprint);
}

void UTSA_CombatAttributeSet::OnRep_ModuleCooldown(const FGameplayAttributeData& OldModuleCooldown)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, ModuleCooldown, OldModuleCooldown);
}

void UTSA_CombatAttributeSet::OnRep_PropUseSpeed(const FGameplayAttributeData& OldPropUseSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, PropUseSpeed, OldPropUseSpeed);
}

void UTSA_CombatAttributeSet::OnRep_PhysicalResistance(const FGameplayAttributeData& OldPhysicalResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, PhysicalResistance, OldPhysicalResistance)
}

void UTSA_CombatAttributeSet::OnRep_EnergyResistance(const FGameplayAttributeData& OldEnergyResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, EnergyResistance, OldEnergyResistance)
}

void UTSA_CombatAttributeSet::OnRep_StructureResistance(const FGameplayAttributeData& OldStructureResistance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, StructureResistance, OldStructureResistance)
}