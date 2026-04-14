// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_OccupyProgressBar.generated.h"

class UProgressBar;
class UTextBlock;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_OccupyProgressBar : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetupOccupyProgressBar(const FText& InText, float InTime);
	
	UFUNCTION(BlueprintImplementableEvent)
	void PlayProgressBarAnimation();
	
	UPROPERTY(BlueprintReadWrite)
	FText OccupyText;
	
	UPROPERTY(BlueprintReadWrite)
	float OccupyTime;
};
