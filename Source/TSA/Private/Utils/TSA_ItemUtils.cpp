// Dark Trace Studio Works


#include "Utils/TSA_ItemUtils.h"

#include "Game/States/TSA_TestGameState.h"
#include "Items/TSA_InventoryItem.h"
#include "Items/Component/TSA_ItemComponent.h"
#include "Items/DataAssets/TSA_ItemDataAsset.h"
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

bool UTSA_ItemUtils::CheckItemTypes(UTSA_InventoryItem* ItemA, UTSA_InventoryItem* ItemB)
{
	FTSA_ItemManifestBase ItemDataA = ItemA->GetItemManifest();
	FTSA_ItemManifestBase ItemDataB = ItemB->GetItemManifest();
	
	return ItemDataA.ItemDataHandle.DataTable == ItemDataB.ItemDataHandle.DataTable && ItemDataA.ItemDataHandle.RowName == ItemDataB.ItemDataHandle.RowName;
}

bool UTSA_ItemUtils::GetBondDefinition(UObject* WorldContextObject, const FGameplayTag& BondTag,
	FTSA_BondDefinition& OutBondDef)
{
	ATSA_TestGameState* GameState = Cast<ATSA_TestGameState>(WorldContextObject->GetWorld()->GetGameState());
	if (!GameState) return false;
	if (auto BondDef = GameState->GlobalBondDatabase->BondMap.Find(BondTag))
	{
		OutBondDef = *BondDef;
		return true;
	}
	return false;
}

