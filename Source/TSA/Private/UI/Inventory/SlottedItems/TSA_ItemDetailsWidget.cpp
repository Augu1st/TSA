// Dark Trace Studio Works


#include "UI/Inventory/SlottedItems/TSA_ItemDetailsWidget.h"

#include "GameplayTagContainer.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Game/States/TSA_TestGameState.h"
#include "Items/DataAssets/TSA_ItemDataAsset.h"
#include "Systems/EquipmentSystem/TSA_BondManagerComp.h"

void UTSA_ItemDetailsWidget::SetUpItemDetails_Implementation(const FInstancedStruct& ItemManifestStruct)
{
}

TArray<FText> UTSA_ItemDetailsWidget::FindBondNameByTags(const FGameplayTagContainer& ItemBonds)
{
	TArray<FText> BondNames;
	
	// 获取羁绊数据库
	ATSA_AgentCharacter* AgentCharacter = Cast<ATSA_AgentCharacter>(GetOwningPlayer()->GetPawn());
	UTSA_BondManagerComp* BondManagerComp = AgentCharacter->GetBondManagerComp();
	UTSA_BondDatabase* BondData = Cast<ATSA_TestGameState>(GetWorld()->GetGameState())->GlobalBondDatabase;
	
	for (const FGameplayTag& BondTag : ItemBonds)
	{
		if (BondData->BondMap.Contains(BondTag))
		{
			BondNames.Add(BondData->BondMap[BondTag].BondName);
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
