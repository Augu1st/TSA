// Dark Trace Studio Works


#include "Player/TSA_PlayerState.h"

#include "AbilitySystem/AttributeSets/TSA_CombatAttributeSet.h"
#include "AbilitySystem/AttributeSets/TSA_CoreAttributeSet.h"
#include "AbilitySystem/AttributeSets/TSA_VitalAttributeSet.h"
#include "AbilitySystem/AttributeSets/TSA_ResourceAttributeSet.h"
#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"

ATSA_PlayerState::ATSA_PlayerState()
{
	SetNetUpdateFrequency(100.f); // 网络更新频率
	
	InitASC();
	InitAttributeSets();
}

UAbilitySystemComponent* ATSA_PlayerState::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void ATSA_PlayerState::InitASC()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTSA_AbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Mixed);
}

void ATSA_PlayerState::InitAttributeSets()
{
	VitalSet = CreateDefaultSubobject<UTSA_VitalAttributeSet>(TEXT("HealthSet"));
	CombatSet = CreateDefaultSubobject<UTSA_CombatAttributeSet>(TEXT("CombatSet"));
	CoreSet = CreateDefaultSubobject<UTSA_CoreAttributeSet>(TEXT("CoreSet"));
	ResourceSet = CreateDefaultSubobject<UTSA_ResourceAttributeSet>(TEXT("ResourceSet"));
}
