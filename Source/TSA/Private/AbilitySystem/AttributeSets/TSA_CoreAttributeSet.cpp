// Dark Trace Studio Works


#include "AbilitySystem/AttributeSets/TSA_CoreAttributeSet.h"

#include "Net/UnrealNetwork.h"

UTSA_CoreAttributeSet::UTSA_CoreAttributeSet()
{
	InitMastery(10.f);
	InitReaction(10.f);
	InitCalculation(10.f);
	InitObservation(10.f);
	InitTenacity(10.f);
	InitResonance(10.f);
}

void UTSA_CoreAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CoreAttributeSet, Mastery, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CoreAttributeSet, Reaction, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CoreAttributeSet, Calculation, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CoreAttributeSet, Observation, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CoreAttributeSet, Tenacity, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_CoreAttributeSet, Resonance, COND_None, REPNOTIFY_Always);
}

void UTSA_CoreAttributeSet::OnRep_Mastery(const FGameplayAttributeData& OldMastery)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CoreAttributeSet, Mastery, OldMastery);
}

void UTSA_CoreAttributeSet::OnRep_Reaction(const FGameplayAttributeData& OldReaction)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CoreAttributeSet, Reaction, OldReaction);
}

void UTSA_CoreAttributeSet::OnRep_Calculation(const FGameplayAttributeData& OldCalculation)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CoreAttributeSet, Calculation, OldCalculation);
}

void UTSA_CoreAttributeSet::OnRep_Observation(const FGameplayAttributeData& OldObservation)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CoreAttributeSet, Observation, OldObservation);
}

void UTSA_CoreAttributeSet::OnRep_Tenacity(const FGameplayAttributeData& OldTenacity)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CoreAttributeSet, Tenacity, OldTenacity);
}

void UTSA_CoreAttributeSet::OnRep_Resonance(const FGameplayAttributeData& OldResonance)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_CoreAttributeSet, Resonance, OldResonance);
}
