// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/HUD.h"
#include "AbilitySystem/DataAssets/TSA_AttributeData.h"
#include "TSA_HUD.generated.h"

class UTSA_AbilitySystemComponent;
class UTSA_AttributeMenu;
class UTSA_AttributeMenuController;
struct FOnAttributeChangeData;
class UTSA_HUDWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChanged, FGameplayTag, AttributeTag, float, NewValue);

UCLASS()
class TSA_API ATSA_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	ATSA_HUD();
	virtual void BeginPlay() override;
	void InitAttributesBindings();
	void BroadcastInitAttributes();

	// Attribute Menu
	UTSA_AttributeMenuController* GetAttributeMenuController();
	UTSA_AttributeMenu* GetAttributeMenu();
	void ToggleAttributeMenu();
	//
	
	FOnAttributeChanged OnAttributeChanged;
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTSA_AttributeData> AttributeData;

private:
	void CreateHUDWidget();
	void OnAnyAttributeChange(const FOnAttributeChangeData& Data, FGameplayTag AttributeTag);
	
	TWeakObjectPtr<UTSA_AbilitySystemComponent> ASC;
	
	
	
	// Attribute Menu
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTSA_AttributeMenuController> AttributeMenuControllerClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_AttributeMenuController> AttributeMenuController;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTSA_AttributeMenu> AttributeMenuClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_AttributeMenu> AttributeMenu;
	
	bool bAttributeMenuOpen = false;
	// End of Attribute Menu
	
	
	// HUD Widget
	UPROPERTY(EditDefaultsOnly, Category = "TSA|UI|HUD")
	TSubclassOf<UTSA_HUDWidget> HUDWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_HUDWidget> HUDWidget;
	// End of HUD Widget
};
