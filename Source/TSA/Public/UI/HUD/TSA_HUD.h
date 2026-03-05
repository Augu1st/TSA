// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "TSA_HUD.generated.h"

class UTSA_HUDWidget;
/**
 * 
 */
UCLASS()
class TSA_API ATSA_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;

private:
	
	void CreateHUDWidget();
	
	// HUD Widget
	UPROPERTY(EditDefaultsOnly, Category = "TSA|UI|HUD")
	TSubclassOf<UTSA_HUDWidget> HUDWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_HUDWidget> HUDWidget;
	// End of HUD Widget
};
