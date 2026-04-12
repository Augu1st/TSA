// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffectTypes.h"
#include "Components/ActorComponent.h"

#include "TSA_EquipmentManagerComp.generated.h"


class UTSA_InventoryComponent;
class ATSA_AgentCharacter;
class UTSA_EquipStatFragment;
class UTSA_AbilitySystemComponent;
class UTSA_ScalingFragment;
struct FGameplayEffectSpecHandle;
class UGameplayEffect;
class UTSA_InventoryItem;

USTRUCT()
struct FTSA_ActiveEffectHandles
{
	GENERATED_BODY()
	
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> ActiveEffectHandles;
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TSA_API UTSA_EquipmentManagerComp : public UActorComponent
{
	GENERATED_BODY()

public:
	UTSA_EquipmentManagerComp();
	virtual void BeginPlay() override;
	
	void UpdateArmor(float BaseArmor);
	
	void UsingProp(UTSA_InventoryComponent* Inventory, UTSA_InventoryItem* Item, int32 SlotIndex);
	void EquipItem(UTSA_InventoryComponent* SourceInventory, UTSA_InventoryItem* Item, int32 SourceIndex);
protected:
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
	
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<UGameplayEffect> DynamicEquipGEClass;
	
	UPROPERTY()
	TMap<UTSA_InventoryItem*, FTSA_ActiveEffectHandles> ItemEffectHandles;
	
	float GetAdditiveValue(const TMap<FGameplayAttribute, float>& AttributeScales,UTSA_AbilitySystemComponent* ASC);
	void  ApplyEquipStatFragment(UTSA_InventoryItem* Item,const UTSA_EquipStatFragment* Fragment,UTSA_AbilitySystemComponent* ASC);
	
	void GenerateCurrentArmor(float BaseArmor,UTSA_AbilitySystemComponent* ASC);
	
	UPROPERTY()
	TObjectPtr<ATSA_AgentCharacter> Agent;
	
	/* Props */
	FTimerHandle PropUsingTimer;
	
	UPROPERTY(EditDefaultsOnly, Category = "TSA|Props")
	TSubclassOf<UGameplayEffect> PropUsingGEClass;
	/* End of Props */
};
