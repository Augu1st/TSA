// Dark Trace Studio Works


#include "Utils/TSA_ItemUtils.h"

#include "Items/TSA_InventoryItem.h"
#include "Items/Component/TSA_ItemComponent.h"
#include "Items/Manifest/TSA_ItemManifest.h"

bool UTSA_ItemUtils::GetItemStaticDataFromItemComp(UTSA_ItemComponent* ItemComponent, FTSA_ItemDataRow& OutItemData)
{
	const FTSA_ItemManifestBase& ItemManifest = ItemComponent->GetItemManifest();
	return GetItemStaticFromManifest(ItemManifest, OutItemData);
}

bool UTSA_ItemUtils::GetItemStaticDataFromItem(UTSA_InventoryItem* Item, FTSA_ItemDataRow& OutItemData)
{
	const FTSA_ItemManifestBase& ItemManifest = Item->GetItemManifest();
	return GetItemStaticFromManifest(ItemManifest, OutItemData);
}

FGameplayTag UTSA_ItemUtils::GetItemCategoryFromItem(UTSA_InventoryItem* Item)
{
	FTSA_ItemDataRow ItemData;	
	GetItemStaticDataFromItem(Item,ItemData);
	
	return ItemData.ItemCategory;
}

FGameplayTag UTSA_ItemUtils::GetItemCategoryFromItemComp(UTSA_ItemComponent* ItemComponent)
{
	FTSA_ItemDataRow ItemData;	
	GetItemStaticDataFromItemComp(ItemComponent,ItemData);
	
	return ItemData.ItemCategory;
}

bool UTSA_ItemUtils::GetItemStaticFromManifest(const FTSA_ItemManifestBase& Manifest, FTSA_ItemDataRow& OutItemData)
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
