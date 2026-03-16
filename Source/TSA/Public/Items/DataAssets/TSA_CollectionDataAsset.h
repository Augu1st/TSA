// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "TSA_ItemDataAsset.h"
#include "Items/DataTable/TSA_ItemData.h"
#include "Types/TSA_ItemTypes.h"
#include "TSA_CollectionDataAsset.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class TSA_API UTSA_CollectionDataAsset : public UTSA_ItemDataAsset
{
	GENERATED_BODY()
	
public:
	// 是否启用特质 (低稀有度可以不填)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trait")
	bool bHasTrait = false;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Trait", meta=(EditCondition="bHasTrait"))
	FTSA_ItemTrait ItemTrait;
};
