// Dark Trace Studio Works


#include "UI/BondMenu/TSA_BondTip.h"

#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "UI/BondMenu/TSA_BondTierDescription.h"
#include "Items/DataAssets/TSA_ItemDataAsset.h"
#include "Utils/TSA_ItemUtils.h"

void UTSA_BondTip::SetBondTip(const FGameplayTag& BondTag, int32 CurrentCount)
{
	FTSA_BondDefinition BondDef;
	if (!UTSA_ItemUtils::GetBondDefinition(this,BondTag, BondDef)) return;
	Text_BondName->SetText(BondDef.BondName);
	Text_CurrentCount->SetText(FText::FromString(FString::FromInt(CurrentCount)));
	Text_BondDescription->SetText(BondDef.BondDescription);
	
	for (int32 i = 0; i < BondDef.BondTiers.Num(); i++)
	{
		auto& Tier = BondDef.BondTiers[i];
		UTSA_BondTierDescription* TierDescription = CreateWidget<UTSA_BondTierDescription>(this, TierDescriptionClass);
		bool bActive = false;
		if (CurrentCount>=Tier.RequiredCount)
		{
			// 不能激活下一阶段
			if (i+1==BondDef.BondTiers.Num()) bActive = true;
			else if (i+1<BondDef.BondTiers.Num() && CurrentCount<BondDef.BondTiers[i+1].RequiredCount) bActive = true;
		}
		TierDescription->SetTierDescription(Tier.RequiredCount, BondDef.BondName, Tier.TierDescription,bActive);
		Box_Tiers->AddChild(TierDescription);
	}
}
