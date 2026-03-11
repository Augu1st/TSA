#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"

#include "TSA_ItemData.generated.h"

USTRUCT(BlueprintType)
struct FTSA_ItemDataRow : public FTableRowBase
{
	GENERATED_BODY()
	
	// 名称
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Base")
	FText ItemName = FText::FromString("None");
	
	// 描述
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Base")
	FText ItemDescription = FText::FromString("None");
	
	// 图标
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Base")
	TObjectPtr<UTexture2D> ItemIcon =  nullptr;
	
	// 类别
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Base")
	FGameplayTag ItemCategory = FGameplayTag::EmptyTag;
	
	// 可堆叠性
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Stack")
	bool bStackable = false;
	
	// 最大堆叠数
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Stack")
	int32 MaxStackCount = 1;
	
	// 能量值
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Exchange")
	int32 EnergyValue = 0.f;
	
	// 物质值
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Exchange")
	int32 MatterValue = 0.f;
	
	// 商店价格
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category="Value")
	int32 ShoppingPrice = 0;
	
	// 出售价格
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Value")
	int32 SellingPrice = 0;
	
};
