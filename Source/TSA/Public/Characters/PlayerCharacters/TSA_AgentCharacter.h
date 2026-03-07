// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Characters/TSA_CharacterBase.h"
#include "TSA_AgentCharacter.generated.h"

class UTSA_InteractComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TSA_API ATSA_AgentCharacter : public ATSA_CharacterBase
{
	GENERATED_BODY()

public:
	ATSA_AgentCharacter();
	
protected:
	virtual void BeginPlay() override;
	
private:
	void InitMovement();
	void InitCameraAndArm();
	void InitInteractComponent();
	
	/* Camera */
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, Category = "Camera")
	TObjectPtr<UCameraComponent> Camera;
	/* End of Camera */
	
	/* Interact Component */
	UPROPERTY(EditDefaultsOnly, Category = "TSA|Interaction")
	TSubclassOf<UTSA_InteractComponent> InteractComponentClass;
	
	UPROPERTY(VisibleAnywhere, Category = "TSA|Interaction")
	TObjectPtr<UTSA_InteractComponent> InteractComponent;
	/* End of Interact Component */
};
