// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Blueprint/UserWidget.h"
#include "TSA_QuickSlot.generated.h"

class UTSA_InventoryItem;
class UImage;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_QuickSlot : public UUserWidget
{
	GENERATED_BODY()
	
public:
	void InitSlot(int32 InSlotIndex);
	
	void SetQuickSlot(UTSA_InventoryItem* InItem);
	void ClearQuickSlot();
	
	int32 GetSlotIndex() const { return SlotIndex; }
	void SetSlotIndex(const int32 Index) { SlotIndex = Index; }
	
	const FGameplayTag& GetInputKeyTag() const { return InputKeyTag; };
	void SetInputKeyTag(const FGameplayTag& Tag);

protected:
	/* Widgets */
	UPROPERTY(meta=(BindWidget))
	class UOverlay* Container;
	
	UPROPERTY(meta=(BindWidget))
	TObjectPtr<UImage> Image_QuickSlot;
	
	UPROPERTY()
	FText InputKey;
	
	UPROPERTY(EditAnywhere)
	FSlateBrush Brush_Unoccupied;
	/* End of Widgets */
	
	TWeakObjectPtr<UTSA_InventoryItem> CurrentModule;
	
	UPROPERTY(BlueprintReadOnly)
	bool IsEmpty = true;
	
	UPROPERTY(BlueprintReadOnly)
	int32 SlotIndex;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="TSA|QuickSlot")
	FGameplayTag InputKeyTag;
};
