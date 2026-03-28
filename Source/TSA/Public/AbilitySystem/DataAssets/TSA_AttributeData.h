// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TSA_AttributeData.generated.h"

USTRUCT(BlueprintType)
struct FTSA_AttributeInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag AttributeTag;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttribute Attribute;
};

UCLASS()
class TSA_API UTSA_AttributeData : public UDataAsset
{
	GENERATED_BODY()
	
public:
	FTSA_AttributeInfo FindInfoByTag(const FGameplayTag& Tag) const;
	//FTSA_AttributeInfo FindInfoByAttribute(const FGameplayAttribute& Attribute) const;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTSA_AttributeInfo> AttributeInformation;
};
