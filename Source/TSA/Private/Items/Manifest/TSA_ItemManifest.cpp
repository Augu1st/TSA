
#include "Items/Manifest/TSA_ItemManifest.h"
#include "Items/TSA_InventoryItem.h"


UTSA_InventoryItem* FTSA_ItemManifestBase::MakeManifest(UObject* NewOuter)
{
	UTSA_InventoryItem* Item = NewObject<UTSA_InventoryItem>(NewOuter, UTSA_InventoryItem::StaticClass());
	Item->SetItemManifest(*this);
	
	return Item; 
}
