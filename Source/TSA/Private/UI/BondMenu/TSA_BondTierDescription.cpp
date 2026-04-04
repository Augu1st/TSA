// Dark Trace Studio Works


#include "UI/BondMenu/TSA_BondTierDescription.h"

#include "Components/TextBlock.h"

void UTSA_BondTierDescription::SetTierDescription(int32 TierCount, const FText& BondName, const FText& TierDescription, bool bActive)
{
	FText CountText = FText::Format(FText::FromString("{0} {1}"), TierCount, BondName);
	Text_TierCount->SetText(CountText);
	if (bActive)
	{
		Text_TierCount->SetColorAndOpacity(FLinearColor(0.f, 1.f, 0.f, 1.f));
		Text_TierDescription->SetColorAndOpacity(FLinearColor(0.f, 1.f, 0.f, 1.f));
	}
	Text_TierDescription->SetText(TierDescription);
}
