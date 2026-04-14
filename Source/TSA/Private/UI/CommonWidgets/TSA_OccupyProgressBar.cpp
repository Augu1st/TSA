// Dark Trace Studio Works


#include "UI/CommonWidgets/TSA_OccupyProgressBar.h"

#include "Components/TextBlock.h"

void UTSA_OccupyProgressBar::SetupOccupyProgressBar(const FText& InText, float InTime)
{
	OccupyText = InText;
	OccupyTime = InTime;
	
	PlayProgressBarAnimation();
}
