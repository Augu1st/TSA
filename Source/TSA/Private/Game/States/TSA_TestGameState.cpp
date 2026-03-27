// Dark Trace Studio Works


#include "Game/States/TSA_TestGameState.h"

#include "Net/UnrealNetwork.h"

ATSA_TestGameState::ATSA_TestGameState()
{
}

void ATSA_TestGameState::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ATSA_TestGameState, WorldMassEnergyRatio);
}
