// Dark Trace Studio Works


#include "TSA_InfoMessage.h"
#include "Components/TextBlock.h"

void UTSA_InfoMessage::NativeOnInitialized()
{
	Super::NativeOnInitialized();
	
	SetVisibility(ESlateVisibility::Collapsed);
}

void UTSA_InfoMessage::ShowMessage_Implementation()
{
	SetVisibility(ESlateVisibility::Visible);
	bIsMessageActive = true;
}

void UTSA_InfoMessage::HideMessage_Implementation()
{
	bIsMessageActive = false;
	SetVisibility(ESlateVisibility::Collapsed);
	GetWorld()->GetTimerManager().ClearTimer(MessageTimer);
	Text_Message->SetText(FText::GetEmpty());
}

void UTSA_InfoMessage::SetMessage(const FText& Message)
{
	Text_Message->SetText(Message);
	ShowMessage();
	
	GetWorld()->GetTimerManager().ClearTimer(MessageTimer);
	GetWorld()->GetTimerManager().SetTimer(MessageTimer, this, &UTSA_InfoMessage::HideMessage, MessageLifeTime, false);
}
