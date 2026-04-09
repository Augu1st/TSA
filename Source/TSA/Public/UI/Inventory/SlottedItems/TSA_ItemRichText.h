// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_ItemRichText.generated.h"

class USizeBox;
class URichTextBlock;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_ItemRichText : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetRichText(const FText& Text);
	
	UPROPERTY(meta=(BindWidget))
	USizeBox* SizeBox;
	
	UPROPERTY(meta=(BindWidget))
	URichTextBlock* RichText;
	
};
