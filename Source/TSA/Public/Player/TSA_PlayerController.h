// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TSA_PlayerController.generated.h"

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

protected:
	
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	void InitHUD();
	void InitInventoryComponents();
	
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
	
	/* Inventory Components */
	UPROPERTY(EditDefaultsOnly, Category = "TSA|Inventory")
	TSubclassOf<UTSA_InventoryComponent> InventoryComponentClass;
	
	UPROPERTY(VisibleAnywhere, Category = "TSA|Inventory")
	TObjectPtr<UTSA_InventoryComponent> MainInventoryComp;
	/* End of Inventory Components */
	
	
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
