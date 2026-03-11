// Dark Trace Studio Works


#include "Items/Component/TSA_ItemComponent.h"
#include "Net/UnrealNetwork.h"

UTSA_ItemComponent::UTSA_ItemComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

void UTSA_ItemComponent::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass,ItemManifest);
}

FTSA_ItemManifestBase UTSA_ItemComponent::GetItemManifest() const
{
	return ItemManifest.Get<FTSA_ItemManifestBase>();
}

