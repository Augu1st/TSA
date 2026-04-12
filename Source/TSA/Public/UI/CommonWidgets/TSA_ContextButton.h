// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "UI/Inventory/SlottedItems/TSA_ContextMenu.h"
#include "TSA_ContextButton.generated.h"

class UTSA_ContextMenu;
class FOnContextActionClicked;
class UButton;

UCLASS()
class TSA_API UTSA_ContextButton : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetupButton(const FText& Text, FOnContextActionClicked InActionDelegate, UTSA_ContextMenu* InParentMenu);
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_Action;
	
	UPROPERTY(meta=(BindWidget))
	UButton* Button_Action;
	
private:
	UFUNCTION()
	void OnButtonClicked();
	
	UPROPERTY()
	FOnContextActionClicked ActionDelegate;
	
	UPROPERTY()
	TObjectPtr<UTSA_ContextMenu> ParentMenu;
};
