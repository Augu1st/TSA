// Dark Trace Studio Works


#include "UI/AttributeMenu/TSA_AttributeMenu.h"

#include "Player/TSA_PlayerController.h"
#include "UI/AttributeMenu/TSA_AttributeMenuController.h"

void UTSA_AttributeMenu::InitAttributeMenu(UTSA_AttributeMenuController* Controller)
{
	if (! Controller)return;
	OwningController = Controller;
	OwningController->OnAttributeMenuChanged.AddDynamic(this, &UTSA_AttributeMenu::UpdateAttributeValue);
}

void UTSA_AttributeMenu::ToggleMenu()
{
	ATSA_PlayerController* PC = GetOwningPlayer<ATSA_PlayerController>();
	if (!PC) return;
	PC->ToggleAttributeMenu();
}
