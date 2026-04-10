// Dark Trace Studio Works


#include "AbilitySystem/AttributeSets/TSA_ResourceAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

UTSA_ResourceAttributeSet::UTSA_ResourceAttributeSet()
{
	InitEnergy(100.f);
	InitMaxEnergy(200.f);
	InitEnergyRegenRate(0.f);
	InitEnergyConsumeRate(0.f);
	InitEnergyNetFlow(0.f);
	
	InitMatter(50.f);
	InitMaxMatter(100.f);
	InitMatterRegenRate(0.f);
	InitMatterConsumeRate(0.f);
	InitMatterNetFlow(0.f);
	
	InitConversionRate(0.5f);

	InitPrintSpeed(1.f);
	InitSearchSpeed(1.f);
}

void UTSA_ResourceAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, Energy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, MaxEnergy, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, EnergyRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, EnergyConsumeRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, EnergyNetFlow, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, Matter, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, MaxMatter, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, MatterRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, MatterConsumeRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, MatterNetFlow, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, ConversionRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, PrintSpeed, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_ResourceAttributeSet, SearchSpeed, COND_None, REPNOTIFY_Always);
}

void UTSA_ResourceAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetEnergyAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxEnergy());
	}
	if (Attribute == GetMatterAttribute())
	{
		NewValue = FMath::Clamp(NewValue, 0.f, GetMaxMatter());
	}
}

void UTSA_ResourceAttributeSet::PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue)
{
	Super::PostAttributeChange(Attribute, OldValue, NewValue);
	
	if (Attribute == GetEnergyRegenRateAttribute() || Attribute == GetEnergyConsumeRateAttribute())
	{
		SetEnergyNetFlow(GetEnergyRegenRate() - GetEnergyConsumeRate());
	}
	if (Attribute == GetMatterRegenRateAttribute() || Attribute == GetMatterConsumeRateAttribute())
	{
		SetMatterNetFlow(GetMatterRegenRate() - GetMatterConsumeRate());
	}
}

void UTSA_ResourceAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetEnergyAttribute())
	{
		SetEnergy(FMath::Clamp(GetEnergy(), 0.f, GetMaxEnergy()));
	}
	else if (Data.EvaluatedData.Attribute == GetMatterAttribute())
	{
		SetMatter(FMath::Clamp(GetMatter(), 0.f, GetMaxMatter()));
	}
	else if (Data.EvaluatedData.Attribute == GetEnergyRegenRateAttribute() ||
		Data.EvaluatedData.Attribute == GetEnergyConsumeRateAttribute())
	{
		SetEnergyNetFlow(GetEnergyRegenRate() - GetEnergyConsumeRate());
	}
	else if (Data.EvaluatedData.Attribute == GetMatterRegenRateAttribute() ||
		Data.EvaluatedData.Attribute == GetMatterConsumeRateAttribute())
	{
		SetMatterNetFlow(GetMatterRegenRate() - GetMatterConsumeRate());
	}
}

void UTSA_ResourceAttributeSet::OnRep_Energy(const FGameplayAttributeData& OldEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, Energy, OldEnergy);
}

void UTSA_ResourceAttributeSet::OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, MaxEnergy, OldMaxEnergy);
}

void UTSA_ResourceAttributeSet::OnRep_EnergyRegenRate(const FGameplayAttributeData& OldEnergyRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, EnergyRegenRate, OldEnergyRegenRate);
}

void UTSA_ResourceAttributeSet::OnRep_EnergyConsumeRate(const FGameplayAttributeData& OldEnergyConsumeRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, EnergyConsumeRate, OldEnergyConsumeRate);
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

void UTSA_ResourceAttributeSet::OnRep_MatterRegenRate(const FGameplayAttributeData& OldMatterRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, MatterRegenRate, OldMatterRegenRate);
}

void UTSA_ResourceAttributeSet::OnRep_MatterConsumeRate(const FGameplayAttributeData& OldMatterConsumeRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, MatterConsumeRate, OldMatterConsumeRate);
}

void UTSA_ResourceAttributeSet::OnRep_MatterNetFlow(const FGameplayAttributeData& OldMatterNetFlow)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, MatterNetFlow, OldMatterNetFlow);
}

void UTSA_ResourceAttributeSet::OnRep_ConversionRate(const FGameplayAttributeData& OldConversionRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, ConversionRate, OldConversionRate);
}

void UTSA_ResourceAttributeSet::OnRep_PrintSpeed(const FGameplayAttributeData& OldPrintSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, PrintSpeed, OldPrintSpeed);
}

void UTSA_ResourceAttributeSet::OnRep_SearchSpeed(const FGameplayAttributeData& OldSearchSpeed)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_ResourceAttributeSet, SearchSpeed, OldSearchSpeed);
}
