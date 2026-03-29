// Dark Trace Studio Works


#include "UI/HUD/TSA_HUD.h"

#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Player/TSA_PlayerState.h"
#include "UI/AttributeMenu/TSA_AttributeMenuController.h"
#include "UI/AttributeMenu/TSA_AttributeMenu.h"
#include "UI/HUD/TSA_HUDWidget.h"


ATSA_HUD::ATSA_HUD()
{
}

void ATSA_HUD::BeginPlay()
{
	Super::BeginPlay();

}

void ATSA_HUD::CreateHUDWidget()
{
	if (!IsValid(HUDWidgetClass))return;
	HUDWidget = CreateWidget<UTSA_HUDWidget>(GetWorld(),HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport();
	}
	OnAttributeChanged.AddDynamic(HUDWidget,&UTSA_HUDWidget::UpdateAttribute);
}

void ATSA_HUD::InitAttributesBindings()
{
	
	APlayerController* PC = GetOwningPlayerController();
	if (!PC) return;

	ATSA_PlayerState* PS = PC->GetPlayerState<ATSA_PlayerState>();
	if (!PS) return;

	ASC = Cast<UTSA_AbilitySystemComponent>(PS->GetAbilitySystemComponent());
	if (!ASC.IsValid()) return;
	
	for (const FTSA_AttributeInfo& Info : AttributeData->AttributeInformation)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(Info.Attribute).AddUObject(
			this,
			&ATSA_HUD::OnAnyAttributeChange,
			Info.AttributeTag
		);
	}
	CreateHUDWidget();
	BroadcastInitAttributes();
	GetAttributeMenu();
	GetAttributeMenuController()->BroadcastInitAttributes(ASC.Get());
}

void ATSA_HUD::BroadcastInitAttributes()
{
	if (!ASC.IsValid()) return;
	
	for (const FTSA_AttributeInfo& Info : AttributeData->AttributeInformation)
	{
		float Value = ASC->GetNumericAttribute(Info.Attribute);
		OnAttributeChanged.Broadcast(Info.AttributeTag, Value);
	}
}

UTSA_AttributeMenuController* ATSA_HUD::GetAttributeMenuController()
{
	if (!AttributeMenuController)
	{
		AttributeMenuController = NewObject<UTSA_AttributeMenuController>(this,AttributeMenuControllerClass,TEXT("AttributeMenuController"));
		if (ASC.IsValid())
		{
			AttributeMenuController->InitAttributesBindings(ASC.Get());
		}
	}
	return AttributeMenuController;
}

UTSA_AttributeMenu* ATSA_HUD::GetAttributeMenu()
{
	if (!AttributeMenu)
	{
		AttributeMenu = CreateWidget<UTSA_AttributeMenu>(GetWorld(), AttributeMenuClass);
		AttributeMenu->AddToViewport(5);
		AttributeMenu->SetVisibility(ESlateVisibility::Collapsed);
		AttributeMenu->InitAttributeMenu(GetAttributeMenuController());
	}
	return AttributeMenu;
}

void ATSA_HUD::ToggleAttributeMenu()
{
	if (!bAttributeMenuOpen)
	{
		GetAttributeMenu()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		bAttributeMenuOpen = true;
	}
	else
	{
		GetAttributeMenu()->SetVisibility(ESlateVisibility::Collapsed);
		bAttributeMenuOpen = false;
	}
}

void ATSA_HUD::OnAnyAttributeChange(const FOnAttributeChangeData& Data, FGameplayTag AttributeTag)
{
	OnAttributeChanged.Broadcast(AttributeTag, Data.NewValue);
}
