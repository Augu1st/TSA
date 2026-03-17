// Dark Trace Studio Works


#include "Interaction/TSA_InteractComponent.h"

#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Utils/TSA_CommonLibrary.h"


UTSA_InteractComponent::UTSA_InteractComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UTSA_InteractComponent::TickComponent(float DeltaTime, ELevelTick TickType,FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	UpdateInteractableActors();
	UpdateInteractPrompt();
}

void UTSA_InteractComponent::PrimaryInteract()
{
	if (!IsValid(CurrentActor)) return;
	if (ITSA_InteractionInterface::Execute_GetInteractState(CurrentActor) == ETSA_InteractState::Interactable)
	{
		ITSA_InteractionInterface::Execute_PrimaryInteract(CurrentActor,GetWorld()->GetFirstPlayerController());
	}
}

void UTSA_InteractComponent::SetInteractionEnabled(bool bEnabled)
{
	if (bEnabled == IsComponentTickEnabled()) return;
	
	SetComponentTickEnabled(bEnabled);
	
	if (!bEnabled)
	{
		if (IsValid(CurrentActor))
		{
			ITSA_InteractionInterface::Execute_HidePrompt(CurrentActor);
		}
		ShowInteractableActorsHint(false);
		
		InteractableActors.Empty();
		CurrentActor = nullptr;
		LastActor = nullptr;
	}
}

void UTSA_InteractComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UTSA_InteractComponent::UpdateInteractableActors()
{
	ShowInteractableActorsHint(false);
	InteractableActors.Empty();
	const TArray<AActor*> IgnoreActors = {GetOwner()};
	InteractableActors = UTSA_CommonLibrary::FindInteractableActorsInRange(GetOwner(),InteractHintDistance,ObjectTypes,IgnoreActors);
	ShowInteractableActorsHint(true);
}

void UTSA_InteractComponent::UpdateInteractPrompt()
{
	if (IsValid(LastActor)) ITSA_InteractionInterface::Execute_HidePrompt(LastActor);
	LastActor = CurrentActor;
	
	CurrentActor = FindClosestInteractableActor();
	if (IsValid(CurrentActor)) ITSA_InteractionInterface::Execute_ShowPrompt(CurrentActor);
}

void UTSA_InteractComponent::ShowInteractableActorsHint(const bool bShow)
{
	for (const auto& Actor : InteractableActors)
	{
		if (!Actor->Implements<UTSA_InteractionInterface>()) continue;
		if (bShow) ITSA_InteractionInterface::Execute_ShowHint(Actor);
		else ITSA_InteractionInterface::Execute_HideHint(Actor);
	}
}

AActor* UTSA_InteractComponent::FindClosestInteractableActor()
{
	float MinDistance = InteractableDistance;
	AActor* ClosestActor = nullptr;
	for (const auto& Actor : InteractableActors)
	{
		float Distance = FVector::Distance(GetOwner()->GetActorLocation(),Actor->GetActorLocation());
		if (Distance < MinDistance)
		{
			MinDistance = Distance;
			ClosestActor = Actor;
		}
	}
	return ClosestActor;
}





