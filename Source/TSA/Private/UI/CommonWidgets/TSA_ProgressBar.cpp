// Dark Trace Studio Works


#include "UI/CommonWidgets/TSA_ProgressBar.h"

#include "Components/ProgressBar.h"
#include "Components/SizeBox.h"

void UTSA_ProgressBar::SetBarSize(float NewWidth, float NewHeight)
{
	SizeBox_Root->SetWidthOverride(NewWidth);
	SizeBox_Root->SetHeightOverride(NewHeight);
}

void UTSA_ProgressBar::UpdateBarPercent(float NewPercent)
{
	NewPercent = FMath::Clamp(NewPercent, 0.f, 1.f);
	ProgressBar->SetPercent(NewPercent);
}
