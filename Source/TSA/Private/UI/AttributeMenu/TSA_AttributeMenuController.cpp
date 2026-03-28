// Dark Trace Studio Works


#include "UI/AttributeMenu/TSA_AttributeMenuController.h"
#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"

void UTSA_AttributeMenuController::InitAttributesBindings(UTSA_AbilitySystemComponent* ASC)
{
	if (!ASC) return;
	
	for (const FTSA_AttributeInfo& Info : AttributeMenuData->AttributeInformation)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(Info.Attribute).AddUObject(
			this,
			&UTSA_AttributeMenuController::AttributeMenuChanged,
			Info.AttributeTag
		);
		float Value =ASC->GetNumericAttribute(Info.Attribute);
	}
}

void UTSA_AttributeMenuController::BroadcastInitAttributes(UTSA_AbilitySystemComponent* ASC)
{
	if (!ASC) return;
	
	for (const FTSA_AttributeInfo& Info : AttributeMenuData->AttributeInformation)
	{
		float Value =ASC->GetNumericAttribute(Info.Attribute);
		OnAttributeMenuChanged.Broadcast(Info.AttributeTag, Value);
	}
}

void UTSA_AttributeMenuController::AttributeMenuChanged(const FOnAttributeChangeData& Data, FGameplayTag AttributeTag)
{
	OnAttributeMenuChanged.Broadcast(AttributeTag, Data.NewValue);	
}

