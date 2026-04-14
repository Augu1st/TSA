// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "StructUtils/InstancedStruct.h"
#include "AttributeSet.h"
#include "TSA_ItemDetailsWidget.generated.h"

struct FTSA_StatModifier;

namespace EGameplayModOp
{
	enum Type : int;
}

class UTSA_EquipStatFragment;
class UTSA_ItemRichText;
class UVerticalBox;
struct FGameplayTagContainer;
/**
 * 
 */
UCLASS()
class TSA_API UTSA_ItemDetailsWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	TArray<FText> FindBondNameByTags(const FGameplayTagContainer&  ItemBonds);
	
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable, Category = "TSA|Item Details")
	void SetUpItemDetails(const FInstancedStruct& ItemManifestStruct);
	
	void ClearRichText();
	
	void AnalyzeStatModifier(const FTSA_StatModifier& StatModifier,FText& AttributeText);
	FString GetAttributeString(const FGameplayAttribute& Attribute,const FString& ValueString);
	FString GetValueString(const TEnumAsByte<EGameplayModOp::Type>& ModifierOp,float Value);
	
	UPROPERTY(meta = (BindWidget))
	UVerticalBox* Box_Fragment;
	
private:
	void AddRichText(const FText& Text);
	
	UPROPERTY(EditAnywhere,Category = "TSA|Item Details")
	TSubclassOf<UTSA_ItemRichText> ItemRichTextClass;
	
	UPROPERTY()
	TArray<UTSA_ItemRichText*> RichTexts;
};
