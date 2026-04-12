// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "TSA_ContextMenu.generated.h"

class UTSA_ContextButton;
class UButton;
class UVerticalBox;
DECLARE_DYNAMIC_DELEGATE(FOnContextActionClicked);

UCLASS()
class TSA_API UTSA_ContextMenu : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void AddMenuOption(const FText& OptionText, FOnContextActionClicked OnClickedDelegate);
	
	void SetMenuPosition(FVector2D ScreenPosition);
	
	UFUNCTION()
	void CloseMenu();
	
protected:
	virtual void NativeConstruct() override;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UVerticalBox> VBox_MenuOptions;
	
	UPROPERTY(meta = (BindWidget))
	TObjectPtr<UButton> Button_CloseMenu;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "TSA|ContextMenu")
	TSubclassOf<UTSA_ContextButton> ContextButtonClass;
};
