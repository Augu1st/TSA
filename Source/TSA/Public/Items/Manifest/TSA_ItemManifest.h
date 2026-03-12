#pragma once

#include "CoreMinimal.h"
#include "StructUtils/InstancedStruct.h"
#include "Items/DataAssets/TSA_EquipmentDataAsset.h"
#include "Items/DataAssets/TSA_PropDataAsset.h"
#include "Items/DataAssets/TSA_CollectionDataAsset.h"
#include "Items/DataTable/TSA_ItemData.h"

#include "TSA_ItemManifest.generated.h"

class UTSA_InventoryItem;


// 1. 基类结构体 (提取公共部分)
USTRUCT(BlueprintType)
struct FTSA_ItemManifestBase
{
	GENERATED_BODY()
	
	//获取静态数据
	bool GetItemStaticData(FTSA_ItemDataRow& OutItemData) const;
	
	UTSA_InventoryItem* MakeManifest(UObject* NewOuter) const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TSA|Item")
	TObjectPtr<UTSA_ItemDataAsset> ItemDataAsset = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="TSA|Item", meta=(RowType="TSA_ItemDataRow"))
	FDataTableRowHandle ItemDataHandle;
	
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