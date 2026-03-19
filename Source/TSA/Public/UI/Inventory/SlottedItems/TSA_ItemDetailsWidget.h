// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StructUtils/InstancedStruct.h"
#include "TSA_ItemDetailsWidget.generated.h"

struct FGameplayTagContainer;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_ItemDetailsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<FText> FindBondNameByTags(const FGameplayTagContainer&  ItemBonds);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TSA|Item Details")
	void SetUpItemDetails(const FInstancedStruct& ItemManifestStruct);
	
private:
	UPROPERTY(EditAnywhere)
	UDataTable* BondDataTable;
};
