// Dark Trace Studio Works


#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "UI/Inventory/TSA_InventoryBase.h"

UTSA_InventoryComponent::UTSA_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

}

void UTSA_InventoryComponent::ToggleInventory()
{
	if (GetInventoryMenu())
	{
		if (bInventoryMenuVisible) InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
		else InventoryMenu->SetVisibility(ESlateVisibility::Visible);
		bInventoryMenuVisible = !bInventoryMenuVisible;
	}
}

UTSA_InventoryBase* UTSA_InventoryComponent::GetInventoryMenu()
{
	if (!IsValid(InventoryMenu))
	{
		ConstructInventory();
	}
	return InventoryMenu;
}

void UTSA_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UTSA_InventoryComponent::ConstructInventory()
{
	if (!IsValid(InventoryMenuClass)) return;
	InventoryMenu = CreateWidget<UTSA_InventoryBase>(GetOwner()->GetWorld(),InventoryMenuClass);
	InventoryMenu->AddToViewport();
	InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
}


