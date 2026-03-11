// Dark Trace Studio Works


#include "TSA_InventoryStatics.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"

UTSA_InventoryComponent* UTSA_InventoryStatics::GetInventoryComponent(AActor* Actor)
{
	if (!IsValid(Actor)) return nullptr;
	return Actor->FindComponentByClass<UTSA_InventoryComponent>();
}
