// Dark Trace Studio Works


#include "AbilitySystem/AttributeSets/TSA_CombatAttributeSet.h"

#include "Net/UnrealNetwork.h"

UTSA_CombatAttributeSet::UTSA_CombatAttributeSet()
{
	InitCritDamage(125.f);
	InitCritRate(0.f);
	
	InitDodgeRate(0.f);
	InitResist_Sturdy(0.f);
	InitResist_Toughness(0.f);
	InitResist_Stable(0.f);
	InitResist_Reflect(0.f);
	InitResist_Insulate_E(0.f);
	InitResist_Insulate_H(0.f);
}

void UTSA_CombatAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, CritRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, CritDamage, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, DodgeRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, Resist_Sturdy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, Resist_Toughness, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, Resist_Stable, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, Resist_Reflect, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, Resist_Insulate_E, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CombatAttributeSet, Resist_Insulate_H, COND_None, REPNOTIFY_Always);
}

void UTSA_CombatAttributeSet::OnRep_CritRate(const FGameplayAttributeData& OldCritRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, CritRate, OldCritRate);
}

void UTSA_CombatAttributeSet::OnRep_CritDamage(const FGameplayAttributeData& OldCritDamage)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, CritDamage, OldCritDamage);
}

void UTSA_CombatAttributeSet::OnRep_DodgeRate(const FGameplayAttributeData& OldDodgeRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, DodgeRate, OldDodgeRate);
}

void UTSA_CombatAttributeSet::OnRep_Resist_Sturdy(const FGameplayAttributeData& OldResist_Sturdy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, Resist_Sturdy, OldResist_Sturdy);
}

void UTSA_CombatAttributeSet::OnRep_Resist_Toughness(const FGameplayAttributeData& OldResist_Toughness)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, Resist_Toughness, OldResist_Toughness);
}

void UTSA_CombatAttributeSet::OnRep_Resist_Stable(const FGameplayAttributeData& OldResist_Stable)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, Resist_Stable, OldResist_Stable);
}

void UTSA_CombatAttributeSet::OnRep_Resist_Reflect(const FGameplayAttributeData& OldResist_Reflect)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, Resist_Reflect, OldResist_Reflect);
}

void UTSA_CombatAttributeSet::OnRep_Resist_Insulate_E(const FGameplayAttributeData& OldResist_Insulate_E)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, Resist_Insulate_E, OldResist_Insulate_E);
}

void UTSA_CombatAttributeSet::OnRep_Resist_Insulate_H(const FGameplayAttributeData& OldResist_Insulate_H)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CombatAttributeSet, Resist_Insulate_H, OldResist_Insulate_H);
}
