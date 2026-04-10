#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Types/TSA_ItemTypes.h"
#include "TSA_ItemData.generated.h"

class UTSA_ItemDataAsset;

USTRUCT(BlueprintType)
struct FTSA_ItemDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
	// ID
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Base")
	FName ID;
	
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
