#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "StructUtils/InstancedStruct.h"
#include "Types/TSA_ItemTypes.h"
#include "Items/DataTable/TSA_ItemData.h"
#include "TSA_ItemManifest.generated.h"

class UTSA_InventoryItem;


// 1. 基类结构体 (提取公共部分)
USTRUCT(BlueprintType)
struct FTSA_ItemManifest
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TSA|Item", meta=(RowType="TSA_ItemDataRow"))
	FDataTableRowHandle ItemDataHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TSA|Item")
	int32 StackCount = 1;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TSA|Item")
	TMap<FGameplayTag, float> DynamicStats;
	
	float GetStat(const FGameplayTag& StatTag, float DefaultValue = 0.0f) const
	{
		for (const auto& Pair : DynamicStats)
		{
			UE_LOG(LogTemp, Log, TEXT("GetStat: %s %f"), *StatTag.ToString(), Pair.Value);
		}
		if (DynamicStats.Contains(StatTag))
		{
			return DynamicStats[StatTag];
		}
		return DefaultValue;
	}
	
	void SetStat(const FGameplayTag& StatTag, float NewValue)
	{
		DynamicStats.Add(StatTag) = NewValue;
		for (const auto& Pair : DynamicStats)
		{
			UE_LOG(LogTemp, Log, TEXT("GetStat: %s %f"), *StatTag.ToString(), Pair.Value);
		}
	}
};