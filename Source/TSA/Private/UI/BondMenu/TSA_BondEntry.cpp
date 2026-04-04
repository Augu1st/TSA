// Dark Trace Studio Works


#include "UI/BondMenu/TSA_BondEntry.h"

#include "Components/Border.h"
#include "Components/Image.h"
#include "Items/DataAssets/TSA_ItemDataAsset.h"
#include "UI/BondMenu/TSA_BondTip.h"
#include "Utils/TSA_ItemUtils.h"

void UTSA_BondEntry::SetBondEntry(const FGameplayTag& BondTag, int32 CurrentCount,bool IsActive)
{
	FTSA_BondDefinition BondDef;
	if (!UTSA_ItemUtils::GetBondDefinition(this, BondTag, BondDef)) return;
	
	Image_BondIcon->SetBrushFromTexture(BondDef.BondIcon);
	Image_BondBackground->SetBrush(IsActive ? ActiveBondBackground:PendingBondBackground);
	if (IsActive)
	{
		Image_BondIcon->SetColorAndOpacity(FLinearColor(1,1,1,1));
		Text_BondName->SetText(BondDef.BondName);
		Text_BondCount->SetText(FText::FromString(FString::FromInt(CurrentCount)));
	}
	else
	{
		Border_Text->SetVisibility(ESlateVisibility::Collapsed);
		Image_BondIcon->SetColorAndOpacity(FLinearColor(0.5,0.5,0.5,1));
	}
	BondTip = CreateWidget<UTSA_BondTip>(GetOwningPlayer(),BondTipClass);
	if (BondTip) BondTip->SetBondTip(BondTag,CurrentCount);
}

void UTSA_BondEntry::NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseEnter(InGeometry, InMouseEvent);
	
	GetWorld()->GetTimerManager().SetTimer(BondTipTimerHandle, this, &UTSA_BondEntry::ShowBondTip, 0.5f, false);
}

void UTSA_BondEntry::NativeOnMouseLeave(const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseLeave(InMouseEvent);
	GetWorld()->GetTimerManager().ClearTimer(BondTipTimerHandle);
	SetToolTip(nullptr);
}

void UTSA_BondEntry::ShowBondTip()
{
	if (BondTip)
	{
		SetToolTip(BondTip);
	}
}
