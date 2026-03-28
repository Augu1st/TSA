// Dark Trace Studio Works


#include "UI/HUD/TSA_HUDWidget.h"

#include "TSA_GameplayTags.h"
#include "TSA/TSA.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "Systems/InventorySystem/Utils/TSA_InventoryStatics.h"
#include "Systems/MessageSystem/TSA_UIMessageSubsystem.h"

void UTSA_HUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (APlayerController* PC = GetOwningPlayer())
	{
		UTSA_UIMessageSubsystem* MsgSubsystem = PC->GetLocalPlayer()->GetSubsystem<UTSA_UIMessageSubsystem>();
		if (!IsValid(MsgSubsystem))
		{
			UE_LOG(LogTSA, Warning, TEXT("UTSA_HUDWidget::NativeConstruct : Failed to get UIMessageSubsystem"));
			return;
		}
		MsgSubsystem->OnMessageReceived.AddDynamic(this,&UTSA_HUDWidget::OnNewMessage);
	}
	
	InitAttributeValues();
	InfoMessage = CreateWidget<UTSA_InfoMessage>(GetOwningPlayer(), InfoMessageClass);
	InfoMessage->AddToViewport(10);
}

void UTSA_HUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
}

void UTSA_HUDWidget::SetValueByAttributeTag(FGameplayTag AttributeTag, float NewValue)
{
	if (AttributeValues.Contains(AttributeTag))
	{
		AttributeValues[AttributeTag] = NewValue;
	}
	else
	{
		AttributeValues.Emplace(AttributeTag, NewValue);
	}
}

float UTSA_HUDWidget::GetValueByAttributeTag(FGameplayTag AttributeTag) const
{
	if (AttributeValues.Contains(AttributeTag))
	{
		return AttributeValues[AttributeTag];
	}
	return 0.0f;
}

void UTSA_HUDWidget::InitAttributeValues()
{
	AttributeValues.Reserve(10);
	AttributeValues.Emplace(AttributeTags::Armor, 0.0f);
	AttributeValues.Emplace(AttributeTags::MaxArmor, 0.0f);
	AttributeValues.Emplace(AttributeTags::Health, 0.0f);
	AttributeValues.Emplace(AttributeTags::MaxHealth, 0.0f);
	AttributeValues.Emplace(AttributeTags::Energy, 0.0f);
	AttributeValues.Emplace(AttributeTags::MaxEnergy, 0.0f);
}

void UTSA_HUDWidget::OnNewMessage(const FText& Message)
{
	InfoMessage->SetMessage(Message);
}

