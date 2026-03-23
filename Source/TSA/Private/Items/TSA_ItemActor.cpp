// Dark Trace Studio Works


#include "Items/TSA_ItemActor.h"

#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Items/Component/TSA_ItemComponent.h"


ATSA_ItemActor::ATSA_ItemActor()
{
	PrimaryActorTick.bCanEverTick = false;
	InitItemComponent();
	
	StaticMeshComp->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	StaticMeshComp->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
}

void ATSA_ItemActor::InitItemComponent()
{
	ItemComponent = CreateDefaultSubobject<UTSA_ItemComponent>(TEXT("ItemComponent"));
}

void ATSA_ItemActor::PrimaryInteract_Implementation(APlayerController* Interactor)
{
	if (!Interactor) return;
	ATSA_AgentCharacter* PlayerCharacter = Cast<ATSA_AgentCharacter>(Interactor->GetPawn());
	if (PlayerCharacter)
	{
		PlayerCharacter->PickUpItem(ItemComponent);
	}
}
