// Dark Trace Studio Works


#include "Items/TSA_InventoryItem.h"
#include "Net/UnrealNetwork.h"

void UTSA_InventoryItem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass,ItemManifest);
	
}

void UTSA_InventoryItem::SetItemManifest(const FTSA_ItemManifestBase& InItemManifest)
{
	ItemManifest = FInstancedStruct::Make<FTSA_ItemManifestBase>(InItemManifest);
}

bool UTSA_InventoryItem::GetItemStaticData(struct FTSA_ItemDataRow& OutItemData) const
{
	// 1. 检查 InstancedStruct 是否有效，且包含的是不是我们的 FTSA_ItemManifestBase
	if (ItemManifest.IsValid() && ItemManifest.GetScriptStruct() == FTSA_ItemManifestBase::StaticStruct())
	{
		// 2. 提取出真正的 Manifest 结构体
		const FTSA_ItemManifestBase& Manifest = ItemManifest.Get<FTSA_ItemManifestBase>();

		// 3. 通过 Handle 去 Data Table 里查找数据
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
	}
	return false;
}
