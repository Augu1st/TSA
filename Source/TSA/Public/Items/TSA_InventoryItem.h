// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "Items/Manifest/TSA_ItemManifest.h"

#include "TSA_InventoryItem.generated.h"

/**
 * 
 */
UCLASS()
class TSA_API UTSA_InventoryItem : public UObject
{
	GENERATED_BODY()
	
public:
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	void SetItemManifest(const FTSA_ItemManifestBase& InItemManifest);
	
	UFUNCTION(BlueprintCallable, Category="TSA|Item")
	bool GetItemStaticData(struct FTSA_ItemDataRow& OutItemData) const;
	
private:
	UPROPERTY(VisibleAnywhere, meta = (BaseStruct = "/Script/TSA.TSA_ItmeManifestBase"), Replicated)
	FInstancedStruct ItemManifest;
};
