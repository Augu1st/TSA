// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "TSA_InteractionInterface.h"
#include "GameFramework/Actor.h"
#include "TSA_InteractableActor.generated.h"

class UTSA_PromptWidget;
class UWidgetComponent;

UCLASS()
class TSA_API ATSA_InteractableActor : public AActor, public ITSA_InteractionInterface
{
	GENERATED_BODY()

public:
	ATSA_InteractableActor();

	// ~Interaction Interface
	virtual ETSA_InteractState GetInteractState_Implementation() override { return InteractState; };
	virtual void PrimaryInteract_Implementation(APlayerController* Interactor) override {};
	virtual void ShowHint_Implementation() override;
	virtual void HideHint_Implementation() override;
	virtual void ShowPrompt_Implementation() override;
	virtual void HidePrompt_Implementation() override;
	// ~End of Interaction Interface
protected:
	virtual void BeginPlay() override;
	
	void InitStaticMeshComp();
	void InitInteractWidgetComp();
	
	UPROPERTY(EditAnywhere)
	TObjectPtr<UStaticMeshComponent> StaticMeshComp;
	
	UPROPERTY(EditDefaultsOnly, Category="TSA|Interaction")
	ETSA_InteractState InteractState = ETSA_InteractState::Interactable;
	
	UPROPERTY(EditAnywhere, Category="TSA|Interaction")
	TObjectPtr<UWidgetComponent> InteractWidgetComp;
	
	UPROPERTY(EditAnywhere, Category="TSA|Interaction")
	TSubclassOf<UTSA_PromptWidget> PromptWidgetClass;
	
	UPROPERTY(EditAnywhere, Category="TSA|Interaction")
	FText InteractPromptText = FText::FromString(TEXT("打开"));
	
	UPROPERTY(EditAnywhere, Category="TSA|Interaction")
	FSlateBrush InteractPromptBrush;
};
