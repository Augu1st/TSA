// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Items/Manifest/TSA_ItemManifest.h"
#include "TSA_ItemComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class TSA_API UTSA_ItemComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTSA_ItemComponent();
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	FTSA_ItemManifestBase GetItemManifest() const;
protected:
	
private:
	UPROPERTY(Replicated,EditAnywhere, meta = (BaseStruct = "/Script/TSA.TSA_ItemManifestBase"),Category="TSA|Item")
	FInstancedStruct ItemManifest;
};
