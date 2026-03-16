// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "Engine/DataTable.h"
#include "Items/DataTable/TSA_ItemData.h"
#include "TSA_RandomItemPool.generated.h"

USTRUCT(BlueprintType)
struct FTSA_RarityTableEntry
{
	GENERATED_BODY()
	
	// 1. 指向某一稀有度的 Data Table (比如 DT_Weapons_Legendary)
	// 注：DataTable 本身体积极小（纯文本），这里用硬指针 UDataTable* 是完全合法且推荐的。
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot")
	UDataTable* RarityDataTable = nullptr;

	// 2. 抽中这张表的权重 (比如白装表权重 1000，金装表权重 10)
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot", meta = (ClampMin = "0"))
	int32 TableWeight = 100;
};

UCLASS()
class TSA_API UTSA_RandomItemPool : public UPrimaryDataAsset
{
	GENERATED_BODY()
	
public:
	// 核心函数：执行一次完整的抽奖，返回抽中的物品数据和数量
	UFUNCTION(BlueprintCallable, Category = "Loot")
	bool RollItemFromTables(FDataTableRowHandle& OutItemHandle, int32& OutQuantity) const;
	
	// 配置表和对应的权重
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Loot Settings")
	TArray<FTSA_RarityTableEntry> RarityTables;

	
};
