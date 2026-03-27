// Dark Trace Studio Works


#include "Characters/Enemy/TSA_EnemyBase.h"

#include "AbilitySystem/AttributeSets/TSA_VitalAttributeSet.h"
#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"


ATSA_EnemyBase::ATSA_EnemyBase()
{
	PrimaryActorTick.bCanEverTick = false;
	
}

void ATSA_EnemyBase::BeginPlay()
{
	Super::BeginPlay();
	
	AbilitySystemComponent->InitAbilityActorInfo(this,this);
}

void ATSA_EnemyBase::InitASC()
{
	AbilitySystemComponent = CreateDefaultSubobject<UTSA_AbilitySystemComponent>("AbilitySystemComponent");
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode(EGameplayEffectReplicationMode::Minimal);
}

void ATSA_EnemyBase::InitAttributeSets()
{
	HealthSet = CreateDefaultSubobject<UTSA_VitalAttributeSet>("HealthSet");
}


