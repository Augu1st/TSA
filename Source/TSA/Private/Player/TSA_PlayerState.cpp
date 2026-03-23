// Dark Trace Studio Works


#include "Player/TSA_PlayerState.h"

#include "AbilitySystem/AttributeSets/TSA_HealthAttributeSet.h"
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
	HealthSet = CreateDefaultSubobject<UTSA_HealthAttributeSet>(TEXT("HealthSet"));
}
