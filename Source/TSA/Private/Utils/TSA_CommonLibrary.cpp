// Dark Trace Studio Works


#include "Utils/TSA_CommonLibrary.h"

#include "Interaction/TSA_InteractableActor.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Systems/MessageSystem/TSA_UIMessageSubsystem.h"
#include "Interaction/TSA_InteractionInterface.h"

TArray<AActor*> UTSA_CommonLibrary::FindInteractableActorsInRange(
	const AActor* Caller, const float& Range,const TArray<TEnumAsByte<EObjectTypeQuery>>& ObjectTypes,const TArray<AActor*>& IgnoreActors)
{
	TArray<AActor*> OverlappedActors;
	
	UKismetSystemLibrary::SphereOverlapActors(
		Caller,
		Caller->GetActorLocation(),
		Range,
		ObjectTypes,
		nullptr,
		IgnoreActors,
		OverlappedActors
		);
	
	for (AActor* Actor : OverlappedActors)
	{
		if (!Actor->Implements<UTSA_InteractionInterface>() && !Cast<ATSA_InteractableActor>(Actor))
		{
			OverlappedActors.Remove(Actor);
		}
	}
	return OverlappedActors;
}

