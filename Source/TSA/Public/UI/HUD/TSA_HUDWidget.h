// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/HUD/TSA_InfoMessage.h"
#include "TSA_HUDWidget.generated.h"

class UTSA_InventoryComponent;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_HUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
	
public:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

private:
	
	// Callbacks
	UFUNCTION()
	void OnNewMessage(const FText& Message);
	// End of Callbacks
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InfoMessage> InfoMessage;
};
