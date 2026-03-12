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
	
	const FTSA_ItemManifestBase& GetItemManifest() const { return ItemManifest.Get<FTSA_ItemManifestBase>(); }
	const FTSA_ItemManifestBase* GetItemManifestPtr() const { return ItemManifest.GetPtr<FTSA_ItemManifestBase>(); }
	FTSA_ItemManifestBase& GetItemManifestMutable() { return ItemManifest.GetMutable<FTSA_ItemManifestBase>(); }
	
	FInstancedStruct& GetItemManifestStruct() { return ItemManifest; }

private:
	UPROPERTY(Replicated,EditAnywhere,meta = ( BaseStruct="/Script/TSA.TSA_ItemManifestBase"), Category="TSA|Item")
	FInstancedStruct ItemManifest;
};
