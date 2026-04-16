// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Components/WidgetComponent.h"
#include "TSA_DamageTextComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class TSA_API UTSA_DamageTextComponent : public UWidgetComponent
{
	GENERATED_BODY()

public:
	UTSA_DamageTextComponent();
	
	UFUNCTION(BlueprintImplementableEvent, BlueprintCallable)
	void SetDamageText(float Damage, bool bIsCritical = false, bool bIsHealthDamage = false);
};
