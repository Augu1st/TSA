// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameState.h"
#include "TSA_TestGameState.generated.h"

class UTSA_BondDatabase;
/**
 * 
 */
UCLASS()
class TSA_API ATSA_TestGameState : public AGameState
{
	GENERATED_BODY()
	
public:
	ATSA_TestGameState();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	UPROPERTY(Replicated, BlueprintReadOnly, Category = "TSA|WorldRules")
	float WorldMassEnergyRatio = 10.0f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Bonds")
	TObjectPtr<UTSA_BondDatabase> GlobalBondDatabase;
};
