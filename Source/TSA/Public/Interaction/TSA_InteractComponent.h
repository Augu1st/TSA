// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "TSA_InteractionInterface.h"
#include "Components/ActorComponent.h"
#include "TSA_InteractComponent.generated.h"


class USphereComponent;

UCLASS(Blueprintable,ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TSA_API UTSA_InteractComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTSA_InteractComponent();
	
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	AActor* GetInteractableActor() const { return CurrentActor;}
	
protected:
	virtual void BeginPlay() override;

private:
	void UpdateInteractableActors();
	void UpdateInteractPrompt();
	void ShowInteractableActorsHint(const bool bShow);
	AActor* FindClosestInteractableActor();
	
	UPROPERTY(EditAnywhere, Category = "TSA|Interaction")
	float InteractHintDistance = 1000.f;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Interaction")
	float InteractableDistance = 200.f;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Interaction")
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes = {EObjectTypeQuery::ObjectTypeQuery9};
	
	UPROPERTY()
	TArray<AActor*> InteractableActors; 
	
	UPROPERTY()
	TObjectPtr<AActor> LastActor = nullptr;	
	
	UPROPERTY()
	TObjectPtr<AActor> CurrentActor =  nullptr;
};
