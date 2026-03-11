// Dark Trace Studio Works


#include "Systems/MessageSystem/TSA_MessageUtils.h"
#include "Systems/MessageSystem/TSA_UIMessageSubsystem.h"

UTSA_UIMessageSubsystem* UTSA_MessageUtils::GetUIMessageSubsystem(const AActor* Caller)
{
	APlayerController* PC = Caller->GetWorld()->GetFirstPlayerController();
	if (PC && PC->GetLocalPlayer())
	{
		return PC->GetLocalPlayer()->GetSubsystem<UTSA_UIMessageSubsystem>();
	}
	return nullptr;
}
