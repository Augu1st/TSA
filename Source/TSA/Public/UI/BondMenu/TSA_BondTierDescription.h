// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_BondTierDescription.generated.h"

class UTextBlock;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_BondTierDescription : public UUserWidget
{
	GENERATED_BODY()
public:
	
	void SetTierDescription(int32 TierCount, const FText& BondName,const FText& TierDescription, bool bActive);
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_TierCount;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_TierDescription;
};
