// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/LocalPlayerSubsystem.h"
#include "TSA_UIMessageSubsystem.generated.h"


DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGlobalUIMessage, const FText&, Message);

UCLASS()
class TSA_API UTSA_UIMessageSubsystem : public ULocalPlayerSubsystem
{
	GENERATED_BODY()
	
public:
	
	UFUNCTION(BlueprintCallable)
	void BroadcastUIMessage(const FText& Message);
	
	UPROPERTY(BlueprintAssignable)
	FOnGlobalUIMessage OnMessageReceived;
};
