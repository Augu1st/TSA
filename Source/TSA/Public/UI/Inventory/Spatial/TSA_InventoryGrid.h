// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Types/TSA_GridTypes.h"

#include "TSA_InventoryGrid.generated.h"

/**
 * 
 */
UCLASS()
class TSA_API UTSA_InventoryGrid : public UUserWidget
{
	GENERATED_BODY()
	
public:
	ETSA_GridType GetGridType() const { return GridType; }
	
private:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess = "true"),  Category = "TSA|Inventory|Grid")
	ETSA_GridType GridType = ETSA_GridType::General;
};
