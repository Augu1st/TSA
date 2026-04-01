// Dark Trace Studio Works


#include "AbilitySystem/AttributeSets/TSA_ResourceAttributeSet.h"

#include "Net/UnrealNetwork.h"

UTSA_ResourceAttributeSet::UTSA_ResourceAttributeSet()
{
	InitEnergy(100.f);
	InitMaxEnergy(200.f);
	InitEnergyNetFlow(0.f);
	InitMatter(50.f);
	InitMaxMatter(100.f);
	InitMatterNetFlow(0.f);
	
	InitConversionRate(0.5f);
	InitConversionSpeed(1.f);
	InitPrintSpeed(100.f);
	
	InitPropUseSpeed(1.f);
	InitPropUseEfficiency(1.f);
}

void UTSA_ResourceAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, Energy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, MaxEnergy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, EnergyNetFlow, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, Matter, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, MaxMatter, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, MatterNetFlow, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, ConversionRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, ConversionSpeed, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, PrintSpeed, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, PropUseSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, PropUseEfficiency, COND_None, REPNOTIFY_Always);
}

void UTSA_ResourceAttributeSet::OnRep_Energy(const FGameplayAttributeData& OldEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, Energy, OldEnergy);
}

void UTSA_ResourceAttributeSet::OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, MaxEnergy, OldMaxEnergy);
}

void UTSA_ResourceAttributeSet::OnRep_EnergyNetFlow(const FGameplayAttributeData& OldEnergyNetFlow)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, EnergyNetFlow, OldEnergyNetFlow);
}

void UTSA_ResourceAttributeSet::OnRep_Matter(const FGameplayAttributeData& OldMatter)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, Matter, OldMatter);
}

void UTSA_ResourceAttributeSet::OnRep_MaxMatter(const FGameplayAttributeData& OldMaxMatter)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, MaxMatter, OldMaxMatter);
}

void UTSA_ResourceAttributeSet::OnRep_MatterNetFlow(const FGameplayAttributeData& OldMatterNetFlow)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, MatterNetFlow, OldMatterNetFlow);
}

void UTSA_ResourceAttributeSet::OnRep_ConversionRate(const FGameplayAttributeData& OldConversionRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, ConversionRate, OldConversionRate);
}

void UTSA_ResourceAttributeSet::OnRep_ConversionSpeed(const FGameplayAttributeData& OldConversionSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, ConversionSpeed, OldConversionSpeed);
}

void UTSA_ResourceAttributeSet::OnRep_PrintSpeed(const FGameplayAttributeData& OldPrintSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, PrintSpeed, OldPrintSpeed);
}

void UTSA_ResourceAttributeSet::OnRep_PropUseSpeed(const FGameplayAttributeData& OldPropUseSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, PropUseSpeed, OldPropUseSpeed);
}

void UTSA_ResourceAttributeSet::OnRep_PropUseEfficiency(const FGameplayAttributeData& OldPropUseEfficiency)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, PropUseEfficiency, OldPropUseEfficiency);
}
