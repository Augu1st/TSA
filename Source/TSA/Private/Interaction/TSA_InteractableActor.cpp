// Dark Trace Studio Works


#include "Interaction/TSA_InteractableActor.h"

#include "Components/WidgetComponent.h"
#include "TSA/TSA.h"
#include "UI/Interaction/TSA_PromptWidget.h"


ATSA_InteractableActor::ATSA_InteractableActor()
{
	PrimaryActorTick.bCanEverTick = false;
	
	InitStaticMeshComp();
	InitInteractWidgetComp();
}

void ATSA_InteractableActor::ShowHint_Implementation()
{
	if (IsValid(StaticMeshComp))
	{
		StaticMeshComp->SetRenderCustomDepth(true);
	}
}

void ATSA_InteractableActor::HideHint_Implementation()
{
	if (IsValid(StaticMeshComp))
	{
		StaticMeshComp->SetRenderCustomDepth(false);
	}
}

void ATSA_InteractableActor::ShowPrompt_Implementation()
{
	if (IsValid(InteractWidgetComp))
	{
		InteractWidgetComp->SetVisibility(true);
	}
}

void ATSA_InteractableActor::HidePrompt_Implementation()
{
	if (IsValid(InteractWidgetComp))
	{
		InteractWidgetComp->SetVisibility(false);
	}
}

void ATSA_InteractableActor::BeginPlay()
{
	Super::BeginPlay();
	
	if (IsValid(InteractWidgetComp))
	{
		UTSA_PromptWidget* PromptWidget = Cast<UTSA_PromptWidget>(InteractWidgetComp->GetUserWidgetObject());
		if (!IsValid(PromptWidget))
		{
			UE_LOG(LogTSA, Error, TEXT("%s: InteractWidgetComp don't have a PromptWidget"), *GetName());
			return;
		}
		PromptWidget->SetPromptText(InteractPromptText);
		PromptWidget->SetKeyImage(InteractPromptBrush);
		InteractWidgetComp->SetVisibility(false);
	}
}

void ATSA_InteractableActor::InitStaticMeshComp()
{
	StaticMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMeshComp"));
	StaticMeshComp->SetupAttachment(RootComponent);
	StaticMeshComp->SetCollisionObjectType(ECC_GameTraceChannel9);
}

void ATSA_InteractableActor::InitInteractWidgetComp()
{
	InteractWidgetComp = CreateDefaultSubobject<UWidgetComponent>(TEXT("InteractWidgetComp"));
	InteractWidgetComp->SetupAttachment(StaticMeshComp);
}



