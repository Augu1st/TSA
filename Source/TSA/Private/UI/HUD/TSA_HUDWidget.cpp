// Dark Trace Studio Works


#include "UI/HUD/TSA_HUDWidget.h"
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
}

void UTSA_HUDWidget::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	UTSA_InventoryComponent* InventoryComponent = UTSA_InventoryStatics::GetInventoryComponent(GetOwningPlayer());
	if (IsValid(InventoryComponent))
	{
		InventoryComponent->NewMessage.AddDynamic(this,&UTSA_HUDWidget::OnNewMessage);
	}
}

void UTSA_HUDWidget::OnNewMessage(const FText& Message)
{
	InfoMessage->SetMessage(Message);
}

