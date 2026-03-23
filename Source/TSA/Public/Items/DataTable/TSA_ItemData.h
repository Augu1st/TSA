#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Types/TSA_ItemTypes.h"
#include "GameplayEffect.h"
#include "TSA_ItemData.generated.h"

class UTSA_ItemDataAsset;

USTRUCT(BlueprintType)
struct FTSA_ItemDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
	// 名称
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Base")
	FText Name = FText::FromString("None");
	
	// 描述
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Base")
	FText Description = FText::FromString("None");
	
	// 图标
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Base")
	TObjectPtr<UTexture2D> Icon =  nullptr;
	
	// 类别
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Base")
	FGameplayTag Category = FGameplayTag::EmptyTag;
	
	// 稀有度
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Base")
	ETSA_ItemRarity Rarity = ETSA_ItemRarity::Common;
	
	// 可堆叠性
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Stack")
	bool bStackable = false;
	
	// 最大堆叠数
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Stack")
	int32 MaxStackCount = 1;
	
	// 能量值
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Exchange")
	float EnergyValue = 0.f;
	
	// 物质值
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Exchange")
	float MatterValue = 0.f;
	
	// 商店价格
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Value")
	int32 PriceInShop = 0;
	
	// 出售价格
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Value")
	int32 SellingPrice = 0;
	
	// 数据资产
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Data Asset", meta = (ExcludeBaseClass = "TSA_ItemDataAsset"))
	TSoftObjectPtr<UTSA_ItemDataAsset> ItemDataAsset = nullptr;
	
	// 羁绊
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Bond")
	FGameplayTagContainer BondTags;
};

USTRUCT(BlueprintType)
struct FTSA_ItemTrait // 特质
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText TraitName;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText TraitDescription;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> TraitEffect; 
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> TraitAbility; 
};

// 羁绊的单个阶级
USTRUCT(BlueprintType)
struct FTSA_BondTier
{
	GENERATED_BODY()

	// 触发此阶级需要的收集品数量
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 RequiredCount = 2;

	// 达到该数量时给予的 Buff
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> BondEffect;
	
	// 达到该数量时给予的 Ability
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TSubclassOf<UGameplayAbility> BondAbility;
};

// 羁绊表的一行 (Data Table 结构)
USTRUCT(BlueprintType)
struct FTSA_BondDataRow : public FTableRowBase
{
	GENERATED_BODY()

	// 羁绊名称
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FText BondName;

	// 标识这个羁绊的 Tag (用于和物品身上的 Tag 匹配)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayTag BondTag;
	
	// 羁绊图标
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TObjectPtr<UTexture2D> BondIcon = nullptr;

	// 羁绊的阶级列表 (按 RequiredCount 从小到大排序)
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TArray<FTSA_BondTier> BondTiers;
};
