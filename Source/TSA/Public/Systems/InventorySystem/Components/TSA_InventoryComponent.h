// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Systems/InventorySystem/FastArray/TSA_FastArray.h"
#include "TSA_InventoryComponent.generated.h"

class UTSA_ItemComponent;
class UTSA_InventoryBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemChange, UTSA_InventoryItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryMessage, const FText&,  Message);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class TSA_API UTSA_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTSA_InventoryComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "TSA|Inventory")
	void TryAddItem(UTSA_ItemComponent* ItemComponent);
	
	UFUNCTION(Server, Reliable)
	void Server_AddNewItem(UTSA_ItemComponent* ItemComponent, int32 StackCount);
	
	UFUNCTION(Server, Reliable)
	void Server_AddStacksToItem(UTSA_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder);
	
	void AddRepSubObj(UObject* SubObj);
	
	void ToggleInventory();
	bool IsInventoryOpen() const { return bInventoryMenuOpen;}
	
	UTSA_InventoryBase* GetInventoryMenu();
	
	FInventoryItemChange OnItemAdded;
	FInventoryItemChange OnItemRemoved;
	FInventoryMessage NewMessage;
	
protected:
	virtual void BeginPlay() override;
	
private:
	
	void ConstructInventory();
	
	UPROPERTY(Replicated)
	FTSA_InventoryFastArray InventoryList;
	
	/* Inventory Widget */
	bool bInventoryMenuOpen = false;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory")
	TSubclassOf<UTSA_InventoryBase> InventoryMenuClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_InventoryBase> InventoryMenu;
	/* End of Inventory Widget */
};
