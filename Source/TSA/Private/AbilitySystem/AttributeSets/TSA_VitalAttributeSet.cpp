// Dark Trace Studio Works


#include "AbilitySystem/AttributeSets/TSA_VitalAttributeSet.h"

#include "Net/UnrealNetwork.h"

UTSA_VitalAttributeSet::UTSA_VitalAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitArmor(0.f);
	InitMaxArmor(0.f);
}

void UTSA_VitalAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, MaxArmor, COND_None, REPNOTIFY_Always);
}

void UTSA_VitalAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, Health, OldHealth);
}

void UTSA_VitalAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, MaxHealth, OldMaxHealth);
}

void UTSA_VitalAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, Armor, OldArmor);
}

void UTSA_VitalAttributeSet::OnRep_MaxArmor(const FGameplayAttributeData& OldMaxArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, MaxArmor, OldMaxArmor);
}
