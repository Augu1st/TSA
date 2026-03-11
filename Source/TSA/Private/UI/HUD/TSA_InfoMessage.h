// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_InfoMessage.generated.h"

class UTextBlock;

UCLASS()
class TSA_API UTSA_InfoMessage : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeOnInitialized() override;
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TSA|HUD")
	void ShowMessage();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TSA|HUD")
	void HideMessage();
	
	void SetMessage(const FText& Message);
	
private:
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTextBlock> Text_Message;
	
	UPROPERTY(EditAnywhere, Category = "TSA|HUD")
	float MessageLifeTime = 2.f;
	
	FTimerHandle MessageTimer;
	bool bIsMessageActive = false;
};
