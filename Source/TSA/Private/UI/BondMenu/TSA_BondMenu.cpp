// Dark Trace Studio Works


#include "UI/BondMenu/TSA_BondMenu.h"

#include "Components/VerticalBox.h"
#include "Items/DataAssets/TSA_ItemDataAsset.h"
#include "UI/BondMenu/TSA_BondEntry.h"
#include "UI/BondMenu/TSA_BondMenuController.h"

void UTSA_BondMenu::InitBondMenu(UTSA_BondMenuController* BondMenuController)
{
	if (BondMenuController)
	{
		BondMenuController->OnClearBond.BindUObject(this,&UTSA_BondMenu::ClearBondEntries);
		BondMenuController->OnAddNewBond.BindUObject(this,&UTSA_BondMenu::AddBondEntry);
	}
}

void UTSA_BondMenu::AddBondEntry(const FGameplayTag& BondTag, int32 CurrentCount, bool bIsActive)
{
	UTSA_BondEntry* NewEntry = CreateWidget<UTSA_BondEntry>(this,BondEntryClass);
	NewEntry->SetBondEntry(BondTag,CurrentCount,bIsActive);
	BondEntries.Add(NewEntry);
	Box_BondEntries->AddChildToVerticalBox(NewEntry);
}

void UTSA_BondMenu::ClearBondEntries()
{
	for (auto& Entry : BondEntries)
	{
		Entry->RemoveFromParent();
	}
	BondEntries.Empty();
}
