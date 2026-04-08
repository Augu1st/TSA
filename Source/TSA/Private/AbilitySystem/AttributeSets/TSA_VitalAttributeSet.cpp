// Dark Trace Studio Works


#include "AbilitySystem/AttributeSets/TSA_VitalAttributeSet.h"
#include "Net/UnrealNetwork.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Systems/EquipmentSystem/TSA_EquipmentManagerComp.h"

UTSA_VitalAttributeSet::UTSA_VitalAttributeSet()
{
	InitHealth(100.f);
	InitMaxHealth(100.f);
	InitHealthRegenRate(0.f);
	InitHealthConsumeRate(0.f);
	InitHealthNetFlow(0.f);
	
	InitArmor(0.f);
	InitMaxArmor(0.f);
	InitArmorRegenRate(0.f);
	InitArmorConsumeRate(0.f);
	InitArmorNetFlow(0.f);
}

void UTSA_VitalAttributeSet::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, Health, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, MaxHealth, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, HealthRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, HealthConsumeRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, HealthNetFlow, COND_None, REPNOTIFY_Always);
	
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, Armor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, MaxArmor, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, ArmorRegenRate, COND_None, REPNOTIFY_Always);
	DOREPLIFETIME_CONDITION_NOTIFY(UTSA_VitalAttributeSet, ArmorConsumeRate, COND_None, REPNOTIFY_Always);
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

void UTSA_VitalAttributeSet::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	if (Data.EvaluatedData.Attribute == GetHealthAttribute())
	{
		SetHealth(FMath::Clamp(GetHealth(), 0.f, GetMaxHealth()));
	}
	else if (Data.EvaluatedData.Attribute == GetArmorAttribute())
	{
		SetArmor(FMath::Clamp(GetArmor(), 0.f, GetMaxArmor()));
		UTSA_AbilitySystemComponent* ASC = Cast<UTSA_AbilitySystemComponent>(GetOwningAbilitySystemComponent());
		if (ATSA_AgentCharacter* AgentCharacter = Cast<ATSA_AgentCharacter>(ASC->GetAvatarActor()))
		{
			UTSA_EquipmentManagerComp* EquipmentManagerComp = AgentCharacter->FindComponentByClass<UTSA_EquipmentManagerComp>();
			if (EquipmentManagerComp)
			{
				EquipmentManagerComp->UpdateArmor(GetArmor());
			}
		}
	}
	else if (Data.EvaluatedData.Attribute == GetHealthRegenRateAttribute() ||
		Data.EvaluatedData.Attribute == GetHealthConsumeRateAttribute())
	{
		SetHealthNetFlow(GetHealthRegenRate() - GetHealthConsumeRate() );
	}
	else if (Data.EvaluatedData.Attribute == GetArmorRegenRateAttribute() ||
		Data.EvaluatedData.Attribute == GetArmorConsumeRateAttribute())
	{
		SetArmorNetFlow(GetArmorRegenRate() - GetArmorConsumeRate());
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

void UTSA_VitalAttributeSet::OnRep_HealthRegenRate(const FGameplayAttributeData& OldHealthRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, HealthRegenRate, OldHealthRegenRate);
}

void UTSA_VitalAttributeSet::OnRep_HealthConsumeRate(const FGameplayAttributeData& OldHealthConsumeRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, HealthConsumeRate, OldHealthConsumeRate);
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

void UTSA_VitalAttributeSet::OnRep_ArmorRegenRate(const FGameplayAttributeData& OldArmorRegenRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, ArmorRegenRate, OldArmorRegenRate);
}

void UTSA_VitalAttributeSet::OnRep_ArmorConsumeRate(const FGameplayAttributeData& OldArmorConsumeRate)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, ArmorConsumeRate, OldArmorConsumeRate);
}

void UTSA_VitalAttributeSet::OnRep_ArmorNetFlow(const FGameplayAttributeData& OldArmorNetFlow)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY(UTSA_VitalAttributeSet, ArmorNetFlow, OldArmorNetFlow);
}
