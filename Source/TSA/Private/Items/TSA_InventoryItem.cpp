// Dark Trace Studio Works


#include "Items/TSA_InventoryItem.h"
#include "Net/UnrealNetwork.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"

void UTSA_InventoryItem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass,ItemManifest);
	
}

void UTSA_InventoryItem::SetItemManifest(const FInstancedStruct& InManifestStruct)
{
	ItemManifest = InManifestStruct;
}

UTSA_InventoryComponent* UTSA_InventoryItem::GetOwningInventoryComponent() const
{
	return GetTypedOuter<UTSA_InventoryComponent>();
}

const FName& UTSA_InventoryItem::GetItemID()
{
	return GetItemManifest().ItemDataHandle.RowName;
}

