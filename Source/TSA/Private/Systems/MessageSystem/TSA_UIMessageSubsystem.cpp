// Dark Trace Studio Works


#include "Systems/MessageSystem/TSA_UIMessageSubsystem.h"

void UTSA_UIMessageSubsystem::BroadcastUIMessage(const FText& Message)
{
	OnMessageReceived.Broadcast(Message);
}
