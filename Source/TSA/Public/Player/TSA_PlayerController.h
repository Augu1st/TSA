// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TSA_PlayerController.generated.h"

class UTSA_InventoryBase;
class UTSA_ItemComponent;
class UTSA_InteractComponent;
class UTSA_InventoryComponent;
class ATSA_HUD;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;


UCLASS()
class TSA_API ATSA_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATSA_PlayerController();
	
	void OpenContainerInventory(UTSA_InventoryComponent* ContainerInventory);
	
	void InitializeInventoryMenu();
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void SetupInputComponent() override;
	
	// Inventory Menu
	
	UTSA_InventoryBase* GetInventoryMenu();
	void ToggleInventory();
	bool IsInventoryOpen() const { return bInventoryMenuOpen;}
	void ClearContainerGrid();
	// End of Inventory Menu
	
private:
	void InitHUD();
	void ConstructInventory();
	
	void PrimaryInteract();
	void InteractWithInventory();
	
	void Move(const FInputActionValue& Value);
	void Jump();
	void StopJumping();
	
	void SetCursorInputMode();
	void SetGameInputMode();
	
	/* HUD */
	UPROPERTY()
	TObjectPtr<ATSA_HUD> HUD;
	/* */
	
	/* 当前已打开的容器 */
	UPROPERTY()
	TWeakObjectPtr<UTSA_InventoryComponent> CurrentContainer;
	
	/* Inventory Widget */
	bool bInventoryMenuOpen = false;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory")
	TSubclassOf<UTSA_InventoryBase> InventoryMenuClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_InventoryBase> InventoryMenu;
	
	bool bInitInventoryMenu = false;
	/* End of Inventory Widget */
	
	
	/* Input Context and Actions */
	UPROPERTY(EditDefaultsOnly, Category = "TSA|Input")
	TArray<TObjectPtr<UInputMappingContext>> InputMappingContexts;
	
	UPROPERTY(EditDefaultsOnly, Category = "TSA|Input")
	TObjectPtr<UInputAction> MoveAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "TSA|Input")
	TObjectPtr<UInputAction> JumpAction;
	/* */
	
	
	/* Interaction Action */
	UPROPERTY(EditDefaultsOnly, Category = "TSA|Interact")
	TObjectPtr<UInputAction> PrimaryInteractAction;
	
	UPROPERTY(EditDefaultsOnly, Category = "TSA|Inventory")
	TObjectPtr<UInputAction> InventoryAction;
	/* */
	
};
