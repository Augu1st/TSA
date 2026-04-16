#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "TSA_InputTypes.generated.h"

USTRUCT(BlueprintType)
struct FTSA_InputDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	FGameplayTag InputTag;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	FText InputName;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Input")
	TSoftObjectPtr<UTexture2D> InputIcon;
};
