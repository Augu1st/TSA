// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_BondTip.generated.h"

struct FGameplayTag;
class UTSA_BondTierDescription;
class UVerticalBox;
class UTextBlock;
struct FTSA_BondDefinition;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_BondTip : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetBondTip(const FGameplayTag& BondTag,int32 CurrentCount);
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_BondName;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_CurrentCount;
	
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* Box_Tiers;	
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_BondDescription;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTSA_BondTierDescription> TierDescriptionClass;
};
