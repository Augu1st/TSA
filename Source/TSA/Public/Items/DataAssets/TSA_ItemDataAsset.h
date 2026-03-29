// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TSA_ItemDataAsset.generated.h"


class UTSA_ItemFragment;

UCLASS(BlueprintType)
class TSA_API UTSA_ItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Base Info")
	FText ItemName = FText::FromString("None");
	
	UPROPERTY(EditAnywhere, Instanced, Category="Item Data")
	TArray<TObjectPtr<UTSA_ItemFragment>> Fragments;
	
	template <typename ResultClass>
	const ResultClass* FindFragment() const
	{
		for (UTSA_ItemFragment* Fragment : Fragments)
		{
			if (const ResultClass* CastedFragment = Cast<ResultClass>(Fragment))
			{
				return CastedFragment;
			}
		}
		return nullptr;
	}
};

