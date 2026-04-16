// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "TSA_UIAsyncLoadSubSystem.generated.h"

struct FStreamableHandle;
class UImage;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_UIAsyncLoadSubSystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable, Category = "TSA|AsyncLoad",meta = (DisplayName = "Set Image Async (Subsystem)"))
	void RequestAsyncLoadImage(UImage* TargetImage, TSoftObjectPtr<UTexture2D> SoftTexture);
	
private:
	TMap<TWeakObjectPtr<UImage>, TSharedPtr<FStreamableHandle>> ActiveLoadTasks;
	
	void CleanupInvalidTasks();
};
