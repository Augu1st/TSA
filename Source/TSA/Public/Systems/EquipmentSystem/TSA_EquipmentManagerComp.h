// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffectTypes.h"
#include "Components/ActorComponent.h"

#include "TSA_EquipmentManagerComp.generated.h"


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

	void UpdateArmor(float BaseArmor);
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
	
	UPROPERTY(EditDefaultsOnly, Category = "Equipment")
	TSubclassOf<UGameplayEffect> DynamicEquipGEClass;
	
	UPROPERTY()
	TMap<UTSA_InventoryItem*, FTSA_ActiveEffectHandles> ItemEffectHandles;
	
	float GetAdditiveValue(const TMap<FGameplayAttribute, float>& AttributeScales,UTSA_AbilitySystemComponent* ASC);
	void  ApplyEquipStatFragment(UTSA_InventoryItem* Item,const UTSA_EquipStatFragment* Fragment,UTSA_AbilitySystemComponent* ASC);
	
	void GenerateCurrentArmor(float BaseArmor,UTSA_AbilitySystemComponent* ASC);
};
