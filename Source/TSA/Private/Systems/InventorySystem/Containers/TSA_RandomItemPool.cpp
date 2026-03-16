// Dark Trace Studio Works


#include "Systems/InventorySystem/Containers/TSA_RandomItemPool.h"

bool UTSA_RandomItemPool::RollItemFromTables(FDataTableRowHandle& OutItemHandle, int32& OutQuantity) const
{
	if (RarityTables.IsEmpty()) return false;

	// ==========================================
	// 阶段一：根据权重，决定抽中哪一张 Data Table
	// ==========================================
	int32 TotalWeight = 0;
	for (const FTSA_RarityTableEntry& Entry : RarityTables)
	{
		// 确保表不是空的，且权重有效，才加入计算
		if (Entry.RarityDataTable && Entry.TableWeight > 0)
		{
			TotalWeight += Entry.TableWeight;
		}
	}

	if (TotalWeight <= 0) return false;

	int32 RandomWeight = FMath::RandRange(0, TotalWeight - 1);
	int32 CurrentWeightSum = 0;
	const FTSA_RarityTableEntry* SelectedEntry = nullptr;

	for (const FTSA_RarityTableEntry& Entry : RarityTables)
	{
		if (!Entry.RarityDataTable || Entry.TableWeight <= 0) continue;

		CurrentWeightSum += Entry.TableWeight;
		if (RandomWeight < CurrentWeightSum)
		{
			SelectedEntry = &Entry;
			break; // 确定了！就是这张表
		}
	}

	if (!SelectedEntry || !SelectedEntry->RarityDataTable) return false;

	// ==========================================
	// 阶段二：在抽中的 Data Table 内，等概率盲抽一个物品
	// ==========================================
    
	// 1. 获取这张表里所有行的名字 (Row Names)
	TArray<FName> RowNames = SelectedEntry->RarityDataTable->GetRowNames();
    
	if (RowNames.IsEmpty()) return false; // 防止表是空的报错

	// 2. 核心：等概率随机！直接在 0 到 数组长度-1 之间 Roll 一个数字
	int32 RandomRowIndex = FMath::RandRange(0, RowNames.Num() - 1);
	FName PickedRowName = RowNames[RandomRowIndex];

	// 3. 根据抽中的行名，把数据拿出来
	FString ContextString(TEXT("Loot Roll"));
	FTSA_ItemDataRow* PickedRowData = SelectedEntry->RarityDataTable->FindRow<FTSA_ItemDataRow>(PickedRowName, ContextString);

	if (PickedRowData)
	{
		// 将抽中的表和行名封装成 Handle 返回
		OutItemHandle.DataTable = SelectedEntry->RarityDataTable;
		OutItemHandle.RowName = PickedRowName;
		
		if (PickedRowData->bStackable) // 可堆叠
		{
			OutQuantity = FMath::RandRange(1, PickedRowData->MaxStackCount); // 随机数量
		}
		else // 不可堆叠
		{
			OutQuantity = 1;
		}
		return true;  
	}

	return false;
}
