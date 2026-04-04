// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "TSA_ItemDataAsset.generated.h"

class UGameplayAbility;
class UGameplayEffect;
class UTSA_ItemFragment;

UCLASS(BlueprintType)
class TSA_API UTSA_ItemDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Base Info")
	FText ItemName = FText::FromString("None");
	
	UPROPERTY(EditAnywhere, Instanced, Category="Item Data")
	TArray<TObjectPtr<UTSA_ItemFragment>> Fragments;
	
	template <typename ResultClass>
	const ResultClass* FindFragment() const
	{
		for (UTSA_ItemFragment* Fragment : Fragments)
		{
			if (const ResultClass* CastedFragment = Cast<ResultClass>(Fragment))
			{
				return CastedFragment;
			}
		}
		return nullptr;
	}
};

// 羁绊的单个阶级
USTRUCT(BlueprintType)
struct FTSA_BondTier
{
	GENERATED_BODY()

	// 触发此阶级需要的收集品数量
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 RequiredCount = 2;

	// 本阶级效果描述
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText TierDescription;
	
	// 达到该数量时给予的 Buff
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> BondEffect;
	
	// 达到该数量时给予的 Ability
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> BondAbility;
};

// 羁绊表的一行 (Data Table 结构)
USTRUCT(BlueprintType)
struct FTSA_BondDefinition
{
	GENERATED_BODY()

	// 羁绊名称
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText BondName = FText::FromString("");

	// 羁绊描述
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText BondDescription;
	
	// 羁绊图标
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> BondIcon = nullptr;

	// 羁绊的阶级列表 (按 RequiredCount 从小到大排序)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTSA_BondTier> BondTiers;
	
	// 逆羁绊标签
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTagContainer AntiBondTags;
};

UCLASS(BlueprintType)
class TSA_API UTSA_BondDatabase : public UPrimaryDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bonds")
	TMap<FGameplayTag, FTSA_BondDefinition> BondMap;
};