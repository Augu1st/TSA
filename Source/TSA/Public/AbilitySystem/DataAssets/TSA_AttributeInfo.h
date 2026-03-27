// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TSA_AttributeInfo.generated.h"

USTRUCT(BlueprintType)
struct FTSA_AttributeValue
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AttributeTag;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	float Value;
};

USTRUCT(BlueprintType)
struct FTSA_AttributeWithTag
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AttributeTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttribute Attribute;
};

UCLASS()
class TSA_API UTSA_AttributeInfo : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FTSA_AttributeWithTag FindInfoByTag(const FGameplayTag& Tag) const;
	//FTSA_AttributeInfo FindInfoByAttribute(const FGameplayAttribute& Attribute) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTSA_AttributeWithTag> AttributeInformation;
};
