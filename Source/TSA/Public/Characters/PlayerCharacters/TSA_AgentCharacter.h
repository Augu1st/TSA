// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Characters/TSA_CharacterBase.h"
#include "TSA_AgentCharacter.generated.h"

class UTSA_ItemComponent;
class UTSA_InventoryComponent;
class UTSA_InteractComponent;
class UCameraComponent;
class USpringArmComponent;

UCLASS()
class TSA_API ATSA_AgentCharacter : public ATSA_CharacterBase
{
	GENERATED_BODY()

public:
	ATSA_AgentCharacter();
	
	UFUNCTION(BlueprintCallable)
	void PickUpItem(UTSA_ItemComponent* ItemComponent);
	
	UTSA_InventoryComponent* GetInventoryCompByCategory(const FGameplayTag& ItemCategory);
	
protected:
	virtual void BeginPlay() override;
	
private:
	void InitMovement();
	void InitCameraAndArm();
	void InitInteractComponent();
	void InitInventoryComponents();
	
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
	
	/* Inventory Components */
	UPROPERTY(VisibleAnywhere)
	TMap<FGameplayTag, UTSA_InventoryComponent*> InventoryComponentMap;
	
	UPROPERTY(EditDefaultsOnly, Category = "TSA|Inventory")
	TSubclassOf<UTSA_InventoryComponent> InventoryComponentClass;
	
	UPROPERTY(VisibleAnywhere, Category = "TSA|Inventory")
	TObjectPtr<UTSA_InventoryComponent> EquipmentInventoryComp;
	
	UPROPERTY(VisibleAnywhere, Category = "TSA|Inventory")
	TObjectPtr<UTSA_InventoryComponent> PropInventoryComp;
	
	UPROPERTY(VisibleAnywhere, Category = "TSA|Inventory")
	TObjectPtr<UTSA_InventoryComponent> GeneralInventoryComp;
	/* End of Inventory Components */
};
