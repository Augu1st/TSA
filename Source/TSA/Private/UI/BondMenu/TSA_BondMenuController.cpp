// Dark Trace Studio Works


#include "UI/BondMenu/TSA_BondMenuController.h"

#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Items/DataAssets/TSA_ItemDataAsset.h"
#include "Systems/EquipmentSystem/TSA_BondManagerComp.h"

void UTSA_BondMenuController::InitBondDelegate(ATSA_AgentCharacter* Agent)
{
	BondManagerComp = Agent->GetBondManagerComp();
	BondManagerComp->OnBondChanged.AddUObject(this, &UTSA_BondMenuController::OnBondListChanged);
}

void UTSA_BondMenuController::OnBondListChanged(const FTSA_BondCounts& BondCounts)
{
	OnClearBond.ExecuteIfBound();
	const TMap<FGameplayTag,int32>& ActiveBonds = BondCounts.ActiveBondCounts;
	const TMap<FGameplayTag,int32>& PendingBonds = BondCounts.PendingBondCounts;
	for (auto& Pair : ActiveBonds)
	{
		OnAddNewBond.ExecuteIfBound(Pair.Key, Pair.Value, true);
	}
	for (auto& Pair : PendingBonds)
	{
		OnAddNewBond.ExecuteIfBound(Pair.Key, Pair.Value, false);
	}
}