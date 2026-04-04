#pragma once

#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "Items/DataTable/TSA_ItemData.h"
#include "TSA_ItemManifest.generated.h"

class UTSA_InventoryItem;


// 1. 基类结构体 (提取公共部分)
USTRUCT(BlueprintType)
struct FTSA_ItemManifestBase
{
	GENERATED_BODY()
	
	FTSA_ItemManifestBase() {}
	FTSA_ItemManifestBase(const FTSA_ItemManifestBase& InData) = default;
	FTSA_ItemManifestBase& operator=(const FTSA_ItemManifestBase& InData) = default;
	FTSA_ItemManifestBase(FTSA_ItemManifestBase&&) = default;
	FTSA_ItemManifestBase& operator=(FTSA_ItemManifestBase&&) = default;
	virtual ~FTSA_ItemManifestBase() = default;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TSA|Item", meta=(RowType="TSA_ItemDataRow"))
	FDataTableRowHandle ItemDataHandle;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TSA|Item")
	int32 StackCount = 1;
};

// 2. 装备动态数据 
USTRUCT(BlueprintType)
struct FTSA_EquipmentManifest : public FTSA_ItemManifestBase
{ 
	GENERATED_BODY()
	
};

// 3. 道具动态数据 
USTRUCT(BlueprintType)
struct FTSA_PropManifest : public FTSA_ItemManifestBase
{
	GENERATED_BODY()
	
};

// 4. 收集品动态数据 
USTRUCT(BlueprintType)
struct FTSA_CollectionManifest : public FTSA_ItemManifestBase
{
	GENERATED_BODY()

	
};