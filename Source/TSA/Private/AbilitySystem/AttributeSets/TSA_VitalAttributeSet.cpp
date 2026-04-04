// Dark Trace Studio Works


#include "AbilitySystem/AttributeSets/TSA_VitalAttributeSet.h"

#include "Net/UnrealNetwork.h"

UTSA_VitalAttributeSet::UTSA_VitalAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitHealthNetFlow(0.f);
	
	InitArmor(0.f);
	InitMaxArmor(0.f);
	InitArmorNetFlow(0.f);
}

void UTSA_VitalAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, HealthNetFlow, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, MaxArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, ArmorNetFlow, COND_None, REPNOTIFY_Always);
}

void UTSA_VitalAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	if (Attribute == GetHealthAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxHealth());
	}
	if (Attribute == GetArmorAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxArmor());
	}
}

void UTSA_VitalAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, Health, OldHealth);
}

void UTSA_VitalAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, MaxHealth, OldMaxHealth);
}

void UTSA_VitalAttributeSet::OnRep_HealthNetFlow(const FGameplayAttributeData& OldHealthNetFlow)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, HealthNetFlow, OldHealthNetFlow);
}

void UTSA_VitalAttributeSet::OnRep_Armor(const FGameplayAttributeData& OldArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, Armor, OldArmor);
}

void UTSA_VitalAttributeSet::OnRep_MaxArmor(const FGameplayAttributeData& OldMaxArmor)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, MaxArmor, OldMaxArmor);
}

void UTSA_VitalAttributeSet::OnRep_ArmorNetFlow(const FGameplayAttributeData& OldArmorNetFlow)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, ArmorNetFlow, OldArmorNetFlow);
}
