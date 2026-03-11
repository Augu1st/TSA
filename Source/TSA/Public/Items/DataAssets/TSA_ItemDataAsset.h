// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"

#include "TSA_ItemDataAsset.generated.h"


UCLASS(Abstract,BlueprintType)
class TSA_API UTSA_ItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Base Info")
	FText ItemName = FText::FromString("None");
	
};

