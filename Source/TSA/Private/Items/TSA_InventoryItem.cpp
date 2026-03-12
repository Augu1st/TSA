// Dark Trace Studio Works


#include "Items/TSA_InventoryItem.h"
#include "Net/UnrealNetwork.h"
#include "TSA/TSA.h"

void UTSA_InventoryItem::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	UObject::GetLifetimeReplicatedProps(OutLifetimeProps);
	
	DOREPLIFETIME(ThisClass,ItemManifest);
	
}

void UTSA_InventoryItem::SetItemManifest(const FTSA_ItemManifestBase& InItemManifest)
{
	ItemManifest = FInstancedStruct::Make<FTSA_ItemManifestBase>(InItemManifest);
}

