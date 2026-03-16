// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_PromptWidget.generated.h"

class UTextBlock;
class UImage;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_PromptWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetPromptText(const FText& Text);
	UFUNCTION(BlueprintCallable)
	void SetKeyImage(const FSlateBrush Brush);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Prompt;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UImage> Image_Key;
};
