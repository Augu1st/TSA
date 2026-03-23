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

FVector UTSA_CommonLibrary::GetRandomLocationAtPlayerFoot(const AActor* PlayerActor, float TraceDistance, float Radius)
{
	if (!PlayerActor) return FVector::ZeroVector;

	FVector Start = PlayerActor->GetActorLocation();
	// 获取半径内随机点
	float RandX = FMath::FRandRange(-Radius, Radius);
	float RandY = FMath::FRandRange(-Radius, Radius);
	Start += FVector(RandX, RandY, 0);
	FVector End = Start - FVector(0, 0, TraceDistance);
    
	FHitResult HitResult;
	FCollisionQueryParams Params;
	Params.AddIgnoredActor(PlayerActor); 
	
	bool bHit = PlayerActor->GetWorld()->LineTraceSingleByChannel(
		HitResult, 
		Start, 
		End, 
		ECC_Visibility, 
		Params
	);

	if (bHit)
	{
		return HitResult.Location;
	}
	
	return Start - FVector(0, 0, PlayerActor->GetSimpleCollisionHalfHeight());
}

