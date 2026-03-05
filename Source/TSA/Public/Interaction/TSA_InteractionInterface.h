// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "TSA_InteractionInterface.generated.h"

// This class does not need to be modified.
UINTERFACE()
class UTSA_InteractionInterface : public UInterface
{
	GENERATED_BODY()
};

UENUM()
enum class EInteractStates :uint8
{
	None,
	Uninteractable,
	Interactable,
	Interacting,
	Interacted
};

class TSA_API ITSA_InteractionInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void PrimaryInteract(AActor* Caller);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowHint();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideHint();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowPrompt();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HidePrompt();
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	EInteractStates GetInteractState();
};
