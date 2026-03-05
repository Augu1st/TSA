// Dark Trace Studio Works


#include "UI/HUD/TSA_HUD.h"
#include "UI/HUD/TSA_HUDWidget.h"


void ATSA_HUD::BeginPlay()
{
	Super::BeginPlay();
	
	CreateHUDWidget();
}

void ATSA_HUD::CreateHUDWidget()
{
	if (!IsValid(HUDWidgetClass))return;
	HUDWidget = CreateWidget<UTSA_HUDWidget>(GetWorld(),HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
}
