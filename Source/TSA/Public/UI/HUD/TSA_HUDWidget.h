// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/DataAssets/TSA_AttributeInfo.h"
#include "Blueprint/UserWidget.h"
#include "UI/HUD/TSA_InfoMessage.h"
#include "TSA_HUDWidget.generated.h"

class UTSA_InventoryComponent;

UCLASS()
class TSA_API UTSA_HUDWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeOnInitialized() override;

	UFUNCTION(BlueprintImplementableEvent)
	void UpdateAttribute(FGameplayTag AttributeTag, float NewValue);
	
protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TSA|UI|Attribute")
	float PlayerHealth;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "TSA|UI|Attribute")
	float PlayerArmor;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TSA|UI|Attribute")
	TArray<FTSA_AttributeValue> AttributeValues;
	
private:
	
	UFUNCTION()
	void OnNewMessage(const FText& Message);
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UTSA_InfoMessage> InfoMessage;
};
