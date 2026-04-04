// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "TSA_BondManagerComp.generated.h"

struct FTSA_RowHandleWrapper;
struct FGameplayTag;
struct FTSA_BondDefinition;
struct FActiveGameplayEffectHandle;
struct FTSA_ItemDataRow;
class ATSA_AgentCharacter;
class UTSA_InventoryItem;
class UTSA_BondDatabase;

USTRUCT(BlueprintType)
struct FTSA_BondCounts
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag,int32> ActiveBondCounts;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TMap<FGameplayTag,int32> PendingBondCounts;
};

DECLARE_MULTICAST_DELEGATE_OneParam(FOnBondChanged,const FTSA_BondCounts&);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TSA_API UTSA_BondManagerComp : public UActorComponent
{
	GENERATED_BODY()

public:
	UTSA_BondManagerComp();
	
	UFUNCTION(BlueprintCallable)
	const TMap<FGameplayTag,int32>& GetActiveBondCounts() const { return ActiveBondCounts; }
	
	UFUNCTION(BlueprintCallable)
	const TMap<FGameplayTag,int32>& GetPendingBondCounts() const { return PendingBondCounts; }
	
	FOnBondChanged OnBondChanged;
	
protected:
	virtual void BeginPlay() override;
	void InitInventoryBonding(ATSA_AgentCharacter* Agent);
	
	UFUNCTION()
	void OnConnectorAddItem(UTSA_InventoryItem* Item,int32 SlotIndex);
	
	UFUNCTION()
	void OnConnectorRemoveItem(UTSA_InventoryItem* Item,int32 SlotIndex);
	
	void RecalculateBonds();
	
	// 已激活羁绊
	UPROPERTY(BlueprintReadOnly)
	TMap<FGameplayTag,int32> ActiveBondCounts;
    	
	// 待激活羁绊
	UPROPERTY(BlueprintReadOnly)
	TMap<FGameplayTag,int32> PendingBondCounts;
	
private:
	UPROPERTY()
	TArray<UTSA_InventoryItem*> ItemsInConnector;
	
	// 已激活GE句柄
	UPROPERTY()
	TArray<FActiveGameplayEffectHandle> ActiveBondEffects;
};

