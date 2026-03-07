// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TSA_InventoryComponent.generated.h"


class UTSA_InventoryBase;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class TSA_API UTSA_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTSA_InventoryComponent();

	UFUNCTION(BlueprintCallable)
	void ToggleInventory();
	bool IsInventoryVisible() const { return bInventoryMenuVisible;}
	
	
	UTSA_InventoryBase* GetInventoryMenu();
	
protected:
	virtual void BeginPlay() override;
	
private:
	
	void ConstructInventory();
	
	/* Inventory Widget */
	bool bInventoryMenuVisible = false;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory")
	TSubclassOf<UTSA_InventoryBase> InventoryMenuClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_InventoryBase> InventoryMenu;
	/* End of Inventory Widget */
};
