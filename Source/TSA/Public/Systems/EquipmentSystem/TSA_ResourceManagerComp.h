// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TSA_ResourceManagerComp.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TSA_API UTSA_ResourceManagerComp : public UActorComponent
{
	GENERATED_BODY()

public:
	UTSA_ResourceManagerComp();

protected:
	virtual void BeginPlay() override;

};
