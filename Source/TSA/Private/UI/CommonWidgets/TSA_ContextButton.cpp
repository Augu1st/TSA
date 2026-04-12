// Dark Trace Studio Works


#include "UI/CommonWidgets/TSA_ContextButton.h"

#include "Alembic/AbcGeom/IFaceSet.h"
#include "Components/Button.h"
#include "UI/Inventory/SlottedItems/TSA_ContextMenu.h"

void UTSA_ContextButton::SetupButton(const FText& Text, FOnContextActionClicked InActionDelegate,
	UTSA_ContextMenu* InParentMenu)
{
	if (Text_Action)
	{
		Text_Action->SetText(Text);
	}
	
	ActionDelegate = InActionDelegate;
	ParentMenu = InParentMenu;
}

void UTSA_ContextButton::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (Button_Action)
	{
		Button_Action->OnClicked.AddDynamic(this, &UTSA_ContextButton::OnButtonClicked);
	}
}

void UTSA_ContextButton::OnButtonClicked()
{
	if (ActionDelegate.IsBound())
	{
		ActionDelegate.Execute();
	}
	if (ParentMenu)
	{
		ParentMenu->CloseMenu();
	}
}
