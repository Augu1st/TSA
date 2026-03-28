// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_AttributeMenu.generated.h"

class ATSA_HUD;
struct FGameplayTag;
class UTSA_AttributeMenuController;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_AttributeMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitAttributeMenu(UTSA_AttributeMenuController* Controller);
	
	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAttributeValue(FGameplayTag AttributeTag, float NewValue);
	
	UFUNCTION(BlueprintCallable)
	void ToggleMenu();
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UTSA_AttributeMenuController> OwningController;
};
