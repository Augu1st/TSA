// Dark Trace Studio Works


#include "UI/Inventory/SlottedItems/TSA_ContextMenu.h"

#include "Components/Button.h"
#include "Components/CanvasPanelSlot.h"
#include "Components/VerticalBox.h"
#include "UI/CommonWidgets/TSA_ContextButton.h"
#include "UI/HUD/TSA_HUD.h"

void UTSA_ContextMenu::AddMenuOption(const FText& OptionText, FOnContextActionClicked OnClickedDelegate)
{
	if (!ContextButtonClass || !VBox_MenuOptions) return;
	
	UTSA_ContextButton* NewButton = CreateWidget<UTSA_ContextButton>(this, ContextButtonClass);
	if (NewButton)
	{
		NewButton->SetupButton(OptionText, OnClickedDelegate, this);
		VBox_MenuOptions->AddChild(NewButton);
	}
}

void UTSA_ContextMenu::SetMenuPosition(FVector2D ScreenPosition)
{
	if (UCanvasPanelSlot* CanvasSlot = Cast<UCanvasPanelSlot>(VBox_MenuOptions->Slot))
	{
		CanvasSlot->SetPosition(ScreenPosition);
	}
}

void UTSA_ContextMenu::CloseMenu()
{
	ATSA_HUD* HUD = Cast<ATSA_HUD>(GetOwningPlayer()->GetHUD());
	if (HUD)
	{
		HUD->SetContextMenu(nullptr);
	}
	RemoveFromParent();
}

void UTSA_ContextMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Button_CloseMenu)
	{
		Button_CloseMenu->OnClicked.AddDynamic(this, &UTSA_ContextMenu::CloseMenu);
	}
}
