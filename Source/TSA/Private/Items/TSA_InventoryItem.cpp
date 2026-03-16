// Dark Trace Studio Works


#include "Items/TSA_InventoryItem.h"
#include "Net/UnrealNetwork.h"

void UTSA_InventoryItem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass,ItemManifest);
	
}

void UTSA_InventoryItem::SetItemManifest(const FInstancedStruct& InManifestStruct)
{
	ItemManifest = InManifestStruct;
}

const FName& UTSA_InventoryItem::GetItemID()
{
	return GetItemManifest().ItemDataHandle.RowName;
}

