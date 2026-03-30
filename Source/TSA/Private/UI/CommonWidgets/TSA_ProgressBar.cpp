// Dark Trace Studio Works


#include "UI/CommonWidgets/TSA_ProgressBar.h"

#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

void UTSA_ProgressBar::SetBarColor(FLinearColor InColor)
{
	ProgressBar->SetFillColorAndOpacity(InColor);
}

void UTSA_ProgressBar::SetBarSize(float NewWidth, float NewHeight)
{
	SizeBox_Root->SetWidthOverride(NewWidth);
	SizeBox_Root->SetHeightOverride(NewHeight);
}

void UTSA_ProgressBar::UpdateBarPercent(float InCurrentValue, float InMaxValue)
{
	CurrentValue = InCurrentValue;
	MaxValue = InMaxValue;
	
	float Percent;
	if (MaxValue <= 0) Percent = 0;
	else Percent = FMath::Clamp(CurrentValue / MaxValue, 0.0f, 1.0f);
	ProgressBar->SetPercent(Percent);
}
