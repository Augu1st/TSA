#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilitySystemComponent.h"
#include "TSA_AttributeDataRow.generated.h"

USTRUCT(BlueprintType)
struct FTSA_AttributeDataRow : public FTableRowBase
{ 
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Attributes")
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Attributes")
	FGameplayTag AttributeTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Attributes")
	FText AttributeName;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Attributes")
	FText AttributeDescription;
};