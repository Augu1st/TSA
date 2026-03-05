// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TSA_PlayerController.generated.h"

class ATSA_HUD;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

UCLASS()
class TSA_API ATSA_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
private:
	void InitHUD();
	
	void PrimaryInteract();
	
	void Move(const FInputActionValue& Value);
	void Jump();
	void StopJumping();
	
	/* HUD */
	UPROPERTY()
	TObjectPtr<ATSA_HUD> HUD;
	/* */
	
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
	/* */
	
};
