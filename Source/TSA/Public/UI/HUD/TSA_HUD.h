// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/HUD.h"
#include "AbilitySystem/DataAssets/TSA_AttributeInfo.h"
#include "TSA_HUD.generated.h"

struct FOnAttributeChangeData;
class UTSA_HUDWidget;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeChanged, FGameplayTag, AttributeTag, float, NewValue);

UCLASS()
class TSA_API ATSA_HUD : public AHUD
{
	GENERATED_BODY()
	
public:
	virtual void BeginPlay() override;
	void InitAttributesBindings();
	
	FOnAttributeChanged OnAttributeChanged;
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTSA_AttributeInfo> AttributeInfoAsset;

private:
	void CreateHUDWidget();
	
	void OnAnyAttributeChange(const FOnAttributeChangeData& Data, FGameplayTag AttributeTag);
	
	// HUD Widget
	UPROPERTY(EditDefaultsOnly, Category = "TSA|UI|HUD")
	TSubclassOf<UTSA_HUDWidget> HUDWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_HUDWidget> HUDWidget;
	// End of HUD Widget
};
