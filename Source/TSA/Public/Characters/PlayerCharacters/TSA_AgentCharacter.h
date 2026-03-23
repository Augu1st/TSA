// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Characters/TSA_CharacterBase.h"
#include "TSA_AgentCharacter.generated.h"

class UTSA_InventoryItem;
struct FInstancedStruct;
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
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual void PossessedBy(AController* NewController) override;
	virtual void OnRep_PlayerState() override;	
	
	UFUNCTION(BlueprintCallable)
	void PickUpItem(UTSA_ItemComponent* ItemComponent);
	
	UFUNCTION(BlueprintCallable)
	void PickUpItemInInventory(UTSA_InventoryItem* Item);
	
	UTSA_InventoryComponent* GetInventoryCompByCategory(const FGameplayTag& ItemCategory);
	

protected:
	virtual void BeginPlay() override;

private:
	void InitMovement();
	void InitCameraAndArm();
	void InitInteractComponent();
	void InitInventoryComponents();
	void InitAbilitySystemInfo();
	
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
	TArray<TObjectPtr<UTSA_InventoryComponent>> InventoryComponents;
	
	UPROPERTY(VisibleAnywhere, Replicated, Category = "TSA|Inventory")
	TObjectPtr<UTSA_InventoryComponent> EquipmentInventoryComp;
	
	UPROPERTY(VisibleAnywhere, Replicated, Category = "TSA|Inventory")
	TObjectPtr<UTSA_InventoryComponent> PropInventoryComp;
	
	UPROPERTY(VisibleAnywhere, Replicated, Category = "TSA|Inventory")
	TObjectPtr<UTSA_InventoryComponent> GeneralInventoryComp;
	/* End of Inventory Components */
};
