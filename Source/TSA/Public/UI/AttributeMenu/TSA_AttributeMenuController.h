// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/DataAssets/TSA_AttributeData.h"
#include "UI/WidgetController/TSA_WidgetController.h"
#include "TSA_AttributeMenuController.generated.h"

struct FOnAttributeChangeData;
class UTSA_AbilitySystemComponent;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnAttributeMenuChanged, FGameplayTag, AttributeTag, float, NewValue);

UCLASS(Blueprintable)
class TSA_API UTSA_AttributeMenuController : public UTSA_WidgetController
{
	GENERATED_BODY()
	
public:
	void InitAttributesBindings(UTSA_AbilitySystemComponent* ASC);
	void BroadcastInitAttributes(UTSA_AbilitySystemComponent* ASC);
	
	FOnAttributeMenuChanged OnAttributeMenuChanged;
	
protected:
	UPROPERTY(EditAnywhere)
	TObjectPtr<UTSA_AttributeData> AttributeMenuData;
	
private:
	void AttributeMenuChanged(const FOnAttributeChangeData& Data, FGameplayTag AttributeTag);
};
