// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Items/Manifest/TSA_ItemManifest.h"

#include "TSA_InventoryItem.generated.h"

class UTSA_InventoryComponent;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_InventoryItem : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	virtual bool IsSupportedForNetworking() const override { return true; }
	
	// Getters and Setters
	void SetItemManifest(const FInstancedStruct& InManifestStruct);
	const FTSA_ItemManifestBase& GetItemManifest() const { return ItemManifest.Get<FTSA_ItemManifestBase>(); }
	const FTSA_ItemManifestBase* GetItemManifestPtr() const { return ItemManifest.GetPtr<FTSA_ItemManifestBase>(); }
	FTSA_ItemManifestBase& GetItemManifestMutable() { return ItemManifest.GetMutable<FTSA_ItemManifestBase>(); }
	FInstancedStruct& GetItemManifestStruct() { return ItemManifest; }
	
	UFUNCTION(BlueprintPure, Category = "TSA|Inventory")
	UTSA_InventoryComponent* GetOwningInventoryComponent() const;
	// End of Getters and Setters
	
	const FName& GetItemID();
	
private:
	UPROPERTY(VisibleAnywhere, meta = (BaseStruct = "/Script/TSA.TSA_ItmeManifestBase"), Replicated)
	FInstancedStruct ItemManifest;
};
