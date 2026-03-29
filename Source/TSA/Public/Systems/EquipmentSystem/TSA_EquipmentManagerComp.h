// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "Components/ActorComponent.h"

#include "TSA_EquipmentManagerComp.generated.h"


class UTSA_InventoryItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TSA_API UTSA_EquipmentManagerComp : public UActorComponent
{
	GENERATED_BODY()

public:
	UTSA_EquipmentManagerComp();

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnWeaponEquipped(UTSA_InventoryItem* Item,int32 SlotIndex);
	
	UFUNCTION()
	void OnWeaponUnequipped(UTSA_InventoryItem* Item,int32 SlotIndex);
	
	UFUNCTION()
	void OnArmorEquipped(UTSA_InventoryItem* Item,int32 SlotIndex);
	
	UFUNCTION()
	void OnArmorUnequipped(UTSA_InventoryItem* Item,int32 SlotIndex);
	
	UFUNCTION()
	void OnModuleEquipped(UTSA_InventoryItem* Item,int32 SlotIndex);
	
	UFUNCTION()
	void OnModuleUnequipped(UTSA_InventoryItem* Item,int32 SlotIndex);
	
private:
	UPROPERTY()
	TMap<UTSA_InventoryItem*,FActiveGameplayEffectHandle> ActiveGEHandles;
};
