// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Interaction/TSA_InteractableActor.h"
#include "TSA_ItemActor.generated.h"

class UTSA_ItemComponent;

UCLASS()
class TSA_API ATSA_ItemActor : public ATSA_InteractableActor
{
	GENERATED_BODY()

public:
	ATSA_ItemActor();

protected:
	void InitItemComponent();
	
	virtual void PrimaryInteract_Implementation(APlayerController* Interactor) override;
	
	UPROPERTY(VisibleAnywhere, Category="TSA|Item")
	TObjectPtr<UTSA_ItemComponent> ItemComponent;
};
