// Dark Trace Studio Works


#include "UI/Inventory/SlottedItems/TSA_ItemDetailsWidget.h"

#include "GameplayTagContainer.h"
#include "Items/DataTable/TSA_ItemData.h"

void UTSA_ItemDetailsWidget::SetUpItemDetails_Implementation(const FInstancedStruct& ItemManifestStruct)
{
}

TArray<FText> UTSA_ItemDetailsWidget::FindBondNameByTags(const FGameplayTagContainer& ItemBonds)
{
	TArray<FText> BondNames;
	if (!BondDataTable) return BondNames;

	// 遍历这个物品拥有的所有羁绊 Tag
	for (const FGameplayTag& BondTag : ItemBonds)
	{
		// 🌟 核心魔法：直接把 Tag 转换成 FName 当作行名去查！
		FName RowName = BondTag.GetTagName();
		
		FString ContextString(TEXT("Find Bond By Tag"));
		FTSA_BondDataRow* BondRow = BondDataTable->FindRow<FTSA_BondDataRow>(RowName, ContextString);

		if (BondRow)
		{
			BondNames.Add(BondRow->BondName);
		}
	}
	if (BondNames.Num() < 3)
	{
		for (int32 i = BondNames.Num(); i < 3; i++) 
		{
			BondNames.Add(FText::FromString(""));
		}
	}
	return BondNames;
}
