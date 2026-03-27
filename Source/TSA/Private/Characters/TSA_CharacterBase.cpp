// Dark Trace Studio Works


#include "Characters/TSA_CharacterBase.h"

ATSA_CharacterBase::ATSA_CharacterBase()
{
	PrimaryActorTick.bCanEverTick = false;

}

UAbilitySystemComponent* ATSA_CharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

