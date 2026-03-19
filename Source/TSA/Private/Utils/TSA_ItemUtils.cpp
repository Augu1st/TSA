// Dark Trace Studio Works


#include "Utils/TSA_ItemUtils.h"

#include "Items/TSA_InventoryItem.h"
#include "Items/Component/TSA_ItemComponent.h"
#include "Items/Manifest/TSA_ItemManifest.h"
#include "Items/DataTable/TSA_ItemData.h" 

bool UTSA_ItemUtils::GetItemStaticDataFromItemComp(UTSA_ItemComponent* ItemComponent, FTSA_ItemDataRow& OutItemData)
{
	if (!ItemComponent) return false;
	const FTSA_ItemManifestBase& ItemManifest = ItemComponent->GetItemManifest();
	return GetItemDataFromManifest(ItemManifest, OutItemData);
}

bool UTSA_ItemUtils::GetItemStaticDataFromItem(UTSA_InventoryItem* Item, FTSA_ItemDataRow& OutItemData)
{
	if (!Item) return false;
	const FTSA_ItemManifestBase& ItemManifest = Item->GetItemManifest();
	return GetItemDataFromManifest(ItemManifest, OutItemData);
}

// 【关键同步修改】：签名里的 FInstancedStruct 加上了 const
bool UTSA_ItemUtils::GetItemStaticDataFromManifestStruct(const FInstancedStruct& ItemManifestStruct, FTSA_ItemDataRow& OutItemData)
{
	if (!ItemManifestStruct.IsValid()) return false;
	
	// FInstancedStruct 具有 const 版本的 Get() 方法，所以这里完美兼容
	const FTSA_ItemManifestBase& ItemManifest = ItemManifestStruct.Get<FTSA_ItemManifestBase>();
	return GetItemDataFromManifest(ItemManifest, OutItemData);
}

FGameplayTag UTSA_ItemUtils::GetItemCategoryFromManifest(const FTSA_ItemManifestBase& Manifest)
{
	FTSA_ItemDataRow ItemData;	
	GetItemDataFromManifest(Manifest, ItemData);
	
	return ItemData.Category; // 注意：根据你之前的定义，是 ItemCategory 而不是 Category
}

FGameplayTag UTSA_ItemUtils::GetItemCategoryFromItem(UTSA_InventoryItem* Item)
{
	FTSA_ItemDataRow ItemData;	
	GetItemStaticDataFromItem(Item, ItemData);
	
	return ItemData.Category;
}

FGameplayTag UTSA_ItemUtils::GetItemCategoryFromItemComp(UTSA_ItemComponent* ItemComponent)
{
	FTSA_ItemDataRow ItemData;	
	GetItemStaticDataFromItemComp(ItemComponent, ItemData);
	
	return ItemData.Category;
}

bool UTSA_ItemUtils::GetItemDataFromManifest(const FTSA_ItemManifestBase& Manifest, FTSA_ItemDataRow& OutItemData)
{
	if (Manifest.ItemDataHandle.DataTable != nullptr && !Manifest.ItemDataHandle.RowName.IsNone())
	{
		FString ContextString(TEXT("Item Fetch"));
		FTSA_ItemDataRow* RowPtr = Manifest.ItemDataHandle.DataTable->FindRow<FTSA_ItemDataRow>(Manifest.ItemDataHandle.RowName, ContextString);
            
		if (RowPtr)
		{
			OutItemData = *RowPtr; // 拷贝数据出去
			return true;
		}
	}
	return false;
}