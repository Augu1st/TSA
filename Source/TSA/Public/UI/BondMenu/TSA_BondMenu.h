// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "TSA_BondMenu.generated.h"

struct FGameplayTag;
struct FTSA_BondDefinition;
class UTSA_BondMenuController;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_BondMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitBondMenu(UTSA_BondMenuController* BondMenuController);
	
	UFUNCTION()
	void AddBondEntry(const FGameplayTag& BondTag, int32 CurrentCount, bool bIsActive);
	
	UFUNCTION()
	void ClearBondEntries();
	
	UPROPERTY(meta=(BindWidget))
	UImage* BondSideImage;
	
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* Box_BondEntries;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<class UTSA_BondEntry> BondEntryClass;
	
	UPROPERTY()
	TArray<UTSA_BondEntry*> BondEntries;
};
