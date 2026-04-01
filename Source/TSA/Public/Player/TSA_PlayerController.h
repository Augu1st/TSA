// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerController.h"
#include "TSA_PlayerController.generated.h"

struct FOnAttributeChangeData;
class UTSA_AbilitySystemComponent;
class UTSA_AttributeData;
class UTSA_InventoryBase;
class UTSA_ItemComponent;
class UTSA_InteractComponent;
class UTSA_InventoryComponent;
class ATSA_HUD;
class UInputMappingContext;
class UInputAction;
struct FInputActionValue;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FAttributeChanged, FGameplayTag, AttributeTag, float, NewValue);

UCLASS()
class TSA_API ATSA_PlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	ATSA_PlayerController();
	
	void OpenContainerInventory(UTSA_InventoryComponent* ContainerInventory);

	UFUNCTION(BlueprintCallable, Category = "TSA|Inventory")
	void RequestPickUpItem(UTSA_ItemComponent* ItemComponent);
	
	UFUNCTION(BlueprintCallable, Category = "TSA|Inventory")
	void RequestAutoAddItem(UTSA_InventoryComponent* SourceComp, int32 SourceIndex);
	
	UFUNCTION(BlueprintCallable, Category = "TSA|Inventory")
	void RequestMoveItem(UTSA_InventoryComponent* SourceComp, int32 SourceIndex, UTSA_InventoryComponent* TargetComp, int32 TargetIndex);
	
	UFUNCTION(BlueprintCallable, Category = "TSA|Inventory")
	void RequestDropItem(UTSA_InventoryComponent* SourceComp, int32 SlotIndex);
	
	void ToggleAttributeMenu();
	void ToggleInventory();
	
	UPROPERTY(BlueprintAssignable)
	FAttributeChanged OnAttributeChanged;
	
protected:
	virtual void BeginPlay() override;
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnRep_PlayerState() override;
	virtual void SetupInputComponent() override;
	
	// Inventory Menu
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_PickUpItem(UTSA_ItemComponent* ItemComponent);
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_AutoAddItem(UTSA_InventoryComponent* SourceComp, int32 SourceIndex);
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveItem(UTSA_InventoryComponent* SourceComp, int32 SourceIndex, UTSA_InventoryComponent* TargetComp, int32 TargetIndex);
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_DropItem(UTSA_InventoryComponent* SourceComp, int32 SlotIndex);
	
	UTSA_InventoryBase* GetInventoryMenu();
	bool IsInventoryOpen() const { return bInventoryMenuOpen;}
	void ClearContainerGrid();
	
	void InitAttributesBindings(UTSA_AbilitySystemComponent* ASC);
	void BroadcastInitAttributes(UTSA_AbilitySystemComponent* ASC);
	
	void AttributeChanged(const FOnAttributeChangeData& Data, FGameplayTag AttributeTag);
	// End of Inventory Menu
	
private:
	void ConstructInventory();
	
	void PrimaryInteract();
	void InteractWithInventory();
	void InitializeInventoryMenu();
	
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
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory")
	TObjectPtr<UTSA_AttributeData> AttributeData;
	
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
	
	UPROPERTY(EditDefaultsOnly, Category = "TSA|Attribute")
	TObjectPtr<UInputAction> AttributeMenuAction;
	/* */
	
};
