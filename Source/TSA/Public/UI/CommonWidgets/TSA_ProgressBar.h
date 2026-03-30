// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_ProgressBar.generated.h"

class UTextBlock;
class USizeBox;
class UProgressBar;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_ProgressBar : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetBarColor(FLinearColor InColor);
	
	UFUNCTION(BlueprintCallable)
	void SetBarSize(float NewWidth, float NewHeight);
	
	UFUNCTION(BlueprintCallable)
	void UpdateBarPercent(float InCurrentValue, float InMaxValue);
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<USizeBox> SizeBox_Root;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UProgressBar> ProgressBar;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TSA|ProgressBar")
	float CurrentValue;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TSA|ProgressBar")
	float MaxValue;
};
