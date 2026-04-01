// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "TSA_GameplayTags.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Components/ActorComponent.h"
#include "TSA_ResourceManagerComp.generated.h"

class UTSA_GameplayAbility;
class UGameplayAbility;
class UTSA_InventoryItem;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TSA_API UTSA_ResourceManagerComp : public UActorComponent
{
	GENERATED_BODY()

public:
	UTSA_ResourceManagerComp();

	UFUNCTION(BlueprintCallable,BlueprintAuthorityOnly)
	void TryToConvert();
	
	UFUNCTION(BlueprintCallable)
	void PutModeToEnergy();
	
	UFUNCTION(BlueprintCallable)
	void PutModeToMatter();

	UFUNCTION(BlueprintCallable)
	FGameplayTag GetConverterMode() const {return ConverterMode; };
	
	void SetConverterMode(FGameplayTag NewConverterMode) { ConverterMode = NewConverterMode; };
	
protected:
	virtual void BeginPlay() override;
	void InitInventoryBonding(ATSA_AgentCharacter* Agent);
	
	void ConvertItem(ATSA_AgentCharacter*  Agent);
	
	UFUNCTION()
	void OnConverterAddItem(UTSA_InventoryItem* Item,int32 SlotIndex);
	
	UFUNCTION()
	void OnConverterRemoveItem(UTSA_InventoryItem* Item,int32 SlotIndex);
	
	UFUNCTION()
	void OnPrinterAddItem(UTSA_InventoryItem* Item,int32 SlotIndex);
	
	UFUNCTION()
	void OnPrinterRemoveItem(UTSA_InventoryItem* Item,int32 SlotIndex);

	/* Converter */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TSA|Converter")
	FGameplayTag ConverterMode = EventTags::Converter::ItemToMatter;
	
	UPROPERTY(EditAnywhere)
	float ConverterLevel = 1.0f;
	
	UPROPERTY()
	TObjectPtr<UTSA_InventoryItem> ItemInConverter;
	
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<UGameplayAbility>> ConverterAbilityClasses;
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGameplayEffect> ResourceWatcher;
	/* End of Converter */
	
	UPROPERTY()
	TObjectPtr<UTSA_InventoryItem> ItemInPrinter;
};
