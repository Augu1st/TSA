// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/DataAssets/TSA_AttributeData.h"
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
	
	UFUNCTION(BlueprintCallable)
	void SetValueByAttributeTag(FGameplayTag AttributeTag, float NewValue);
	UFUNCTION(BlueprintCallable)
	float GetValueByAttributeTag(FGameplayTag AttributeTag) const;
	
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TSA|UI|Attribute")
	TMap<FGameplayTag, float> AttributeValues;
	
private:
	void InitAttributeValues();
	
	
	UFUNCTION()
	void OnNewMessage(const FText& Message);
	
	UPROPERTY(EditAnywhere)
	TSubclassOf<UTSA_InfoMessage> InfoMessageClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_InfoMessage> InfoMessage;
};
