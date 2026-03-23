// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Characters/TSA_CharacterBase.h"
#include "TSA_EnemyBase.generated.h"

UCLASS()
class TSA_API ATSA_EnemyBase : public ATSA_CharacterBase
{
	GENERATED_BODY()

public:
	ATSA_EnemyBase();
	
protected:
	virtual void BeginPlay() override;
	
private:
	void InitASC();
	void InitAttributeSets();
	
};
