// Dark Trace Studio Works


#include "UI/HUD/TSA_HUD.h"

#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Player/TSA_PlayerController.h"
#include "Player/TSA_PlayerState.h"
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
	OnAttributeChanged.AddDynamic(HUDWidget,&UTSA_HUDWidget::UpdateAttribute);
}

void ATSA_HUD::InitAttributesBindings()
{
	APlayerController* PC = GetOwningPlayerController();
	if (!PC) return;

	ATSA_PlayerState* PS = PC->GetPlayerState<ATSA_PlayerState>();
	if (!PS) return;

	UAbilitySystemComponent* ASC = PS->GetAbilitySystemComponent();
	if (!ASC) return;
	
	for (const FTSA_AttributeWithTag& Info : AttributeInfoAsset->AttributeInformation)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(Info.Attribute).AddUObject(
			this,
			&ATSA_HUD::OnAnyAttributeChange,
			Info.AttributeTag
		);
	}
}

void ATSA_HUD::OnAnyAttributeChange(const FOnAttributeChangeData& Data, FGameplayTag AttributeTag)
{
	OnAttributeChanged.Broadcast(AttributeTag, Data.NewValue);
}
