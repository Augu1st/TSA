// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "TSA_ItemDataAsset.h"
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
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Collection Info")
	ETSA_ItemRarity Rarity = ETSA_ItemRarity::Common;
};
