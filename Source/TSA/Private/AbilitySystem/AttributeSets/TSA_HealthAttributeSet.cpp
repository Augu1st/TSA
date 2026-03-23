// Dark Trace Studio Works


#include "AbilitySystem/AttributeSets/TSA_HealthAttributeSet.h"

#include "Net/UnrealNetwork.h"

UTSA_HealthAttributeSet::UTSA_HealthAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
}

void UTSA_HealthAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_HealthAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_HealthAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
}

void UTSA_HealthAttributeSet::OnRep_Health(const FGameplayAttributeData& OldHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_HealthAttributeSet, Health, OldHealth);
}

void UTSA_HealthAttributeSet::OnRep_MaxHealth(const FGameplayAttributeData& OldMaxHealth)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_HealthAttributeSet, MaxHealth, OldMaxHealth);
}