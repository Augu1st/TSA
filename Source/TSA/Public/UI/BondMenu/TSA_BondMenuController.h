// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/TSA_WidgetController.h"
#include "TSA_BondMenuController.generated.h"

class UImage;
struct FGameplayTag;
struct FTSA_BondDefinition;
struct FTSA_BondCounts;
class UTSA_BondManagerComp;
class ATSA_AgentCharacter;

DECLARE_DELEGATE(FOnClearBond)
DECLARE_DELEGATE_ThreeParams(FOnAddNewBond,const FGameplayTag&,int32,bool);

UCLASS()
class TSA_API UTSA_BondMenuController : public UTSA_WidgetController
{
	GENERATED_BODY()
	
public:
	void InitBondDelegate(ATSA_AgentCharacter* Agent);
	
	UFUNCTION()
	void OnBondListChanged(const FTSA_BondCounts& BondCounts);
	
	FOnClearBond OnClearBond;
	FOnAddNewBond OnAddNewBond;
	
	TWeakObjectPtr<UTSA_BondManagerComp> BondManagerComp;
};
