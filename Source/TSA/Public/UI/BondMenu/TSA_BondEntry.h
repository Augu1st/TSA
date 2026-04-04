// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "TSA_BondEntry.generated.h"

struct FGameplayTag;
struct FTSA_BondDefinition;
class UTSA_BondTip;
class UBorder;
class UImage;
/**
 * 
 */
UCLASS(BlueprintType)
class TSA_API UTSA_BondEntry : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void SetBondEntry(const FGameplayTag& BondTag, int32 CurrentCount,bool IsActive);
	
	virtual void NativeOnMouseEnter(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;
	virtual void NativeOnMouseLeave(const FPointerEvent& InMouseEvent) override;
	
	void ShowBondTip();
	
	UPROPERTY(meta=(BindWidget))
	UImage* Image_BondIcon;
	
	UPROPERTY(meta=(BindWidget))
	UImage* Image_BondBackground;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_BondName;
	
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Text_BondCount;
	
	UPROPERTY(meta=(BindWidget))
	UBorder* Border_Text;
	
	UPROPERTY(EditAnywhere)
	FSlateBrush ActiveBondBackground;
	
	UPROPERTY(EditAnywhere)
	FSlateBrush PendingBondBackground;
	
	/* BondTip */
	UPROPERTY(EditAnywhere, Category="TSA|BondTip")
	TSubclassOf<UTSA_BondTip> BondTipClass;
	
	UPROPERTY()
	TObjectPtr<UTSA_BondTip> BondTip;
	
	UPROPERTY(EditAnywhere, Category="TSA|BondTip")
	float BondTipDelay = 0.5f;
	
	FTimerHandle BondTipTimerHandle;
	/* End of BondTip */
};
