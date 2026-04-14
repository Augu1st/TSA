// Dark Trace Studio Works


#include "UI/Inventory/SlottedItems/TSA_ItemDetailsWidget.h"

#include "GameplayTagContainer.h"
#include "TSA_GameplayTags.h"
#include "AbilitySystem/AttributeSets/TSA_CombatAttributeSet.h"
#include "AbilitySystem/AttributeSets/TSA_CoreAttributeSet.h"
#include "AbilitySystem/AttributeSets/TSA_ResourceAttributeSet.h"
#include "AbilitySystem/AttributeSets/TSA_VitalAttributeSet.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Components/VerticalBox.h"
#include "Game/TSA_GameInstanceSys.h"
#include "Game/States/TSA_TestGameState.h"
#include "Items/DataAssets/TSA_ItemDataAsset.h"
#include "Items/DataAssets/TSA_ItemFragment.h"
#include "Items/Manifest/TSA_ItemManifest.h"
#include "Systems/EquipmentSystem/TSA_BondManagerComp.h"
#include "UI/Inventory/SlottedItems/TSA_ItemRichText.h"
#include "Utils/TSA_ItemUtils.h"

void UTSA_ItemDetailsWidget::SetUpItemDetails_Implementation(const FInstancedStruct& ItemManifestStruct)
{
	const FTSA_ItemManifest& ItemManifest = ItemManifestStruct.Get<FTSA_ItemManifest>();
	FTSA_ItemDataRow ItemData;
	UTSA_ItemUtils::GetItemStaticDataFromManifestStruct(ItemManifestStruct, ItemData);
	if (UTSA_ItemDataAsset* ItemDataAsset = ItemData.ItemDataAsset.Get())
	{
		// 是否为护甲
		if (const UTSA_ArmorFragment* ArmorFragment = ItemDataAsset->FindFragment<UTSA_ArmorFragment>())
		{
			FString CurrentArmor;
			float ArmorValue = ItemManifest.GetStat(AttributeTags::Armor);
			CurrentArmor.Append(GetAttributeString(UTSA_VitalAttributeSet::GetArmorAttribute(),GetValueString(EGameplayModOp::Additive,ArmorValue)));
			AddRichText(FText::FromString(CurrentArmor));
		}
		if (const UTSA_ConsumeFragment* ConsumeFragment = ItemDataAsset->FindFragment<UTSA_ConsumeFragment>())
		{
			FString Text = TEXT("启用时间: ");
			Text.Append(FString::Printf(TEXT("%.1f秒"),ConsumeFragment->ConsumeTime));
			AddRichText(FText::FromString(Text));
		}
		// 获取装备属性
		if (const UTSA_EquipStatFragment* EquipStatFragment = ItemDataAsset->FindFragment<UTSA_EquipStatFragment>())
		{
			for (const FTSA_StatModifier& StatModifier : EquipStatFragment->Modifiers)
			{
				FText AttributeText;
				AnalyzeStatModifier(StatModifier,AttributeText);
				if (AttributeText.IsEmpty()) continue;
				AddRichText(AttributeText);
			}
		}
		if (const UTSA_InstantStatFragment* InstantStatFragment = ItemDataAsset->FindFragment<UTSA_InstantStatFragment>())
		{
			AddRichText(FText::FromString(TEXT("即时效果: ")));
			for (const FTSA_StatModifier& StatModifier : InstantStatFragment->Modifiers)
			{
				FText AttributeText;
				AnalyzeStatModifier(StatModifier,AttributeText);
				if (AttributeText.IsEmpty()) continue;
				AddRichText(AttributeText);
			}
		}
		if (const UTSA_DurationBuffFragment* DurationBuffFragment = ItemDataAsset->FindFragment<UTSA_DurationBuffFragment>())
		{
			AddRichText(FText::FromString(FString(TEXT("持续效果："))+FString::Printf(TEXT("%.1f秒"),DurationBuffFragment->Duration)));
			for (const FTSA_StatModifier& StatModifier : DurationBuffFragment->Modifiers)
			{
				FText AttributeText;
				AnalyzeStatModifier(StatModifier,AttributeText);
				if (AttributeText.IsEmpty()) continue;
				AddRichText(AttributeText);
			}
		}
	}
}

TArray<FText> UTSA_ItemDetailsWidget::FindBondNameByTags(const FGameplayTagContainer& ItemBonds)
{
	TArray<FText> BondNames;
	
	// 获取羁绊数据库
	ATSA_AgentCharacter* AgentCharacter = Cast<ATSA_AgentCharacter>(GetOwningPlayer()->GetPawn());
	UTSA_BondManagerComp* BondManagerComp = AgentCharacter->GetBondManagerComp();
	UTSA_BondDatabase* BondData = Cast<ATSA_TestGameState>(GetWorld()->GetGameState())->GlobalBondDatabase;
	
	for (const FGameplayTag& BondTag : ItemBonds)
	{
		if (BondData->BondMap.Contains(BondTag))
		{
			BondNames.Add(BondData->BondMap[BondTag].BondName);
		}
	}
	if (BondNames.Num() < 3)
	{
		for (int32 i = BondNames.Num(); i < 3; i++) 
		{
			BondNames.Add(FText::FromString(""));
		}
	}
	return BondNames;
}

void UTSA_ItemDetailsWidget::ClearRichText()
{
	for (UTSA_ItemRichText* RichText : RichTexts)
	{
		RichText->RemoveFromParent();
	}
	RichTexts.Empty();
}

void UTSA_ItemDetailsWidget::AnalyzeStatModifier(const FTSA_StatModifier& StatModifier,FText& AttributeText)
{
	FString ValueString = GetValueString(StatModifier.ModifierOp, StatModifier.Value);
	FString Attribute = GetAttributeString(StatModifier.Attribute,ValueString);
	if (!StatModifier.AttributeScales.IsEmpty())
	{
		FString AttributeScales = "(";
		for (const auto& Pair : StatModifier.AttributeScales)
		{
			AttributeScales.Append(GetAttributeString(Pair.Key,GetValueString(EGameplayModOp::Additive, Pair.Value)));
		}
		AttributeScales.Append(")");
		Attribute.Append(AttributeScales);
	}
	AttributeText = FText::FromString(Attribute);
}

FString UTSA_ItemDetailsWidget::GetAttributeString(const FGameplayAttribute& Attribute,const FString& ValueString)
{
	FString AttributeString;
	AttributeString.Append(ValueString);
	if (UTSA_GameInstanceSys* GameInstanceSys = GetWorld()->GetGameInstance()->GetSubsystem<UTSA_GameInstanceSys>())
	{
		if (GameInstanceSys->AttributeStrings.Contains(Attribute))
		{
			AttributeString.Append(" ");
			AttributeString.Append(GameInstanceSys->AttributeStrings[Attribute]);
			AttributeString.Append(" ");
			return AttributeString;
		}
		
	}
	return FString();
}

FString UTSA_ItemDetailsWidget::GetValueString(const TEnumAsByte<EGameplayModOp::Type>& ModifierOp, float Value)
{
	if (ModifierOp==EGameplayModOp::Multiplicitive || ModifierOp==EGameplayModOp::Division)
		return FString::Printf(TEXT("%.0f%%"),Value*100);
	return FString::Printf(TEXT("+%.1f"),Value);
}

void UTSA_ItemDetailsWidget::AddRichText(const FText& Text)
{
	UTSA_ItemRichText* RichText = CreateWidget<UTSA_ItemRichText>(this, ItemRichTextClass);
	RichText->SetRichText(Text);
	Box_Fragment->AddChild(RichText);
	RichTexts.Add(RichText);
}

