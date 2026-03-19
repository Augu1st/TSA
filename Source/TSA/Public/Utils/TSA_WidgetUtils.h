// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "TSA_WidgetUtils.generated.h"

/**
 * 
 */
UCLASS()
class TSA_API UTSA_WidgetUtils : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintPure, Category = "TSA|Widget Utils", meta = (WorldContext = "WorldContextObject"))
	static FVector2D GetViewportPositionFromMouseEvent(UObject* WorldContextObject, const FPointerEvent& MouseEvent);
	
	static int32 GetIndexFromPosition(const FIntPoint& Position, const int32 Columns);
	static FIntPoint GetPositionFromIndex(const int32 Index, const int32 Columns);
};
