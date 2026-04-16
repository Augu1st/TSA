// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayEffectTypes.h"
#include "TSA_GameplayTags.h"
#include "Components/ActorComponent.h"

#include "TSA_EquipmentManagerComp.generated.h"


class UTSA_QuickGrid;
class UTSA_InventoryGrid;
struct FAttributeBasedFloat;
class UTSA_OccupyProgressBar;
class UTSA_ItemDataAsset;
struct FTSA_StatModifier;
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
	
	void EquipItem(UTSA_InventoryComponent* SourceInventory, UTSA_InventoryItem* Item, int32 SourceIndex);
	void UseProp(UTSA_InventoryComponent* Inventory, UTSA_InventoryItem* Item, int32 SlotIndex);
	
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
	void ApplyEquipStatFragment(UTSA_InventoryItem* Item,const UTSA_EquipStatFragment* Fragment,UTSA_AbilitySystemComponent* ASC);
	void ApplyInstantOrDurationEffect(const TSubclassOf<UGameplayEffect>& EffectClass , UTSA_AbilitySystemComponent* ASC,float Duration = 0.f);
	void GetAttributeBaseMagnitude(FAttributeBasedFloat& AttributeBasedFloat,UTSA_AbilitySystemComponent* ASC, FGameplayAttribute Attribute,float Coefficient = 1.f);
	
	UFUNCTION()
	void ApplyAllEffectOfProp(UTSA_InventoryComponent* Inventory,UTSA_InventoryItem* Item,int32 SlotIndex,UTSA_AbilitySystemComponent* ASC);
	void ApplyUsingPropGE(float InTime,UTSA_AbilitySystemComponent* ASC);
	void GenerateCurrentArmor(float BaseArmor,UTSA_AbilitySystemComponent* ASC);
	
	void CreateQuickGrid();
	
	UPROPERTY()
	TObjectPtr<ATSA_AgentCharacter> Agent;
	
	/* Props */
	FTimerHandle PropUsingTimerHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "TSA|Props")
	TSubclassOf<UGameplayEffect> PropUsingGEClass;
	
	UPROPERTY()
	FGameplayEffectSpecHandle PropUsingGEHandle;
	
	UPROPERTY(EditDefaultsOnly, Category = "TSA|Props")
	TSubclassOf<UTSA_OccupyProgressBar> OccupyProgressBarClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_OccupyProgressBar> OccupyProgressBar;
	/* End of Props */
	
	/* Quick Grid */
	UPROPERTY(EditDefaultsOnly, Category = "TSA|QuickGrid")
	int32 MaxQuickSlotCounts = 5;
	
	UPROPERTY(EditDefaultsOnly, Category = "TSA|QuickGrid")
	TSubclassOf<UTSA_QuickGrid> QuickGridClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_QuickGrid> QuickGrid_Module;
	/* End of Quick Grid */
};
