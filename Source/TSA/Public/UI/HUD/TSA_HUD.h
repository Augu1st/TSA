// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/HUD.h"
#include "AbilitySystem/DataAssets/TSA_AttributeData.h"
#include "TSA_HUD.generated.h"

class UTSA_InventoryComponent;
class UTSA_InventoryBase;
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
	
	void ToggleInventory();
	bool IsInventoryOpen() const { return bInventoryMenuOpen;}
	void OpenContainer(UTSA_InventoryComponent* ContainerInventory);
	
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
	
	UTSA_InventoryBase* GetInventoryMenu();	
	void ConstructInventory();
	void InitializeInventoryMenu();
	
	void ClearContainerGrid();
	
	TWeakObjectPtr<UTSA_AbilitySystemComponent> ASC;
	
	// HUD Widget
	UPROPERTY(EditDefaultsOnly, Category = "TSA|UI|HUD")
	TSubclassOf<UTSA_HUDWidget> HUDWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_HUDWidget> HUDWidget;
	// End of HUD Widget	
	
	/* Inventory Widget */
	UPROPERTY()
	TWeakObjectPtr<UTSA_InventoryComponent> CurrentContainer;
	
	bool bInventoryMenuOpen = false;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory")
	TSubclassOf<UTSA_InventoryBase> InventoryMenuClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_InventoryBase> InventoryMenu;
	
	bool bInitInventoryMenu = false;
	/* End of Inventory Widget */		
	
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
};
