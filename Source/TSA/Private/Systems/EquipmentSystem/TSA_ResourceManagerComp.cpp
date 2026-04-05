// Dark Trace Studio Works


#include "Systems/EquipmentSystem/TSA_ResourceManagerComp.h"

#include "TSA_GameplayTags.h"
#include "AbilitySystem/Abilities/TSA_AbilityTags.h"
#include "AbilitySystem/AttributeSets/TSA_ResourceAttributeSet.h"
#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Game/States/TSA_TestGameState.h"
#include "Items/TSA_InventoryItem.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "TSA/TSA.h"
#include "Utils/TSA_ItemUtils.h"
#include "GameplayAbilities/Public/AbilitySystemBlueprintLibrary.h"
#include "Systems/MessageSystem/TSA_MessageUtils.h"
#include "Systems/MessageSystem/TSA_UIMessageSubsystem.h"


UTSA_ResourceManagerComp::UTSA_ResourceManagerComp()
{
	PrimaryComponentTick.bCanEverTick = false;
	SetIsReplicatedByDefault(true);
}

void UTSA_ResourceManagerComp::TryToConvert()
{
	ATSA_AgentCharacter* Agent = Cast<ATSA_AgentCharacter>(GetOwner());
	if (!Agent || !Agent->HasAuthority()) return;
	UTSA_AbilitySystemComponent* ASC = Agent->GetASC();
	
	if (ConverterMode.MatchesTagExact(EventTags::Converter::ItemToMatter))
	{
		if (ASC->IsMatterFull())
		{
			UTSA_MessageUtils::GetUIMessageSubsystem(GetOwner())->BroadcastUIMessage(FText::FromString(TEXT("物质已满，无法转换！")));
			return;
		}
		ConvertItem(Agent);
	}
	else if (ConverterMode.MatchesTagExact(EventTags::Converter::ItemToEnergy))
	{
		if (ASC->IsEnergyFull())
		{
			UTSA_MessageUtils::GetUIMessageSubsystem(GetOwner())->BroadcastUIMessage(FText::FromString(TEXT("能量已满，无法转换！")));
			return;
		}
		ConvertItem(Agent);
	}
}

void UTSA_ResourceManagerComp::PutModeToEnergy()
{
	if (IsValid(ItemInConverter))
		ConverterMode = EventTags::Converter::ItemToEnergy;
	else
		ConverterMode = EventTags::Converter::MatterToEnergy;
}

void UTSA_ResourceManagerComp::PutModeToMatter()
{
	if (IsValid(ItemInConverter))
		ConverterMode = EventTags::Converter::ItemToMatter;
	else
		ConverterMode = EventTags::Converter::EnergyToMatter;
}

void UTSA_ResourceManagerComp::BeginPlay()
{
	Super::BeginPlay();
	
	ATSA_AgentCharacter* Agent = Cast<ATSA_AgentCharacter>(GetOwner());
	if (!Agent) return;
	InitInventoryBonding(Agent);
	
	UTSA_AbilitySystemComponent* ASC = Agent->GetASC();
	// 判断是否在服务器
	if (ASC && ASC->IsOwnerActorAuthoritative())
	{
		ASC->GiveAbilityWithClassesAndLevel(ConverterAbilityClasses, ConverterLevel);
		
		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(ResourceWatcher, 1.0f, ContextHandle);
		ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
}

void UTSA_ResourceManagerComp::InitInventoryBonding(ATSA_AgentCharacter* Agent)
{
	UTSA_InventoryComponent* ConverterInventory = Agent->GetConverterInventory();
	UTSA_InventoryComponent* PrinterInventory = Agent->GetPrinterInventory();
	
	if (ConverterInventory)
	{
		ConverterInventory->OnItemAdded.AddDynamic(this, &UTSA_ResourceManagerComp::OnConverterAddItem);
		ConverterInventory->OnItemRemoved.AddDynamic(this, &UTSA_ResourceManagerComp::OnConverterRemoveItem);
	}
	if (PrinterInventory)
	{
		PrinterInventory->OnItemAdded.AddDynamic(this, &UTSA_ResourceManagerComp::OnPrinterAddItem);
		PrinterInventory->OnItemRemoved.AddDynamic(this, &UTSA_ResourceManagerComp::OnPrinterRemoveItem);
	}
}

void UTSA_ResourceManagerComp::ConvertItem(ATSA_AgentCharacter* Agent)
{
	if (!IsValid(ItemInConverter)) return;
	FTSA_ItemDataRow ItemData;
	UTSA_ItemUtils::GetItemStaticDataFromItem(ItemInConverter, ItemData);
	
	// 统一转换为能量值，方便GA计算转换时间
	float MatterValue = ItemData.MatterValue;
	const float ConvertRatio = Cast<ATSA_TestGameState>(GetWorld()->GetGameState())->WorldMassEnergyRatio;
	if (ItemData.EnergyValue>0.f)MatterValue += ItemData.EnergyValue / ConvertRatio;
	
	FGameplayEventData Payload;
	Payload.Instigator = Agent;
	Payload.Target = Agent;
	Payload.EventMagnitude = MatterValue;
	Payload.EventTag = ConverterMode;
	
	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(GetOwner(), ConverterMode, Payload);
}

void UTSA_ResourceManagerComp::OnConverterAddItem(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	if (SlotIndex == 0)ItemInConverter = Item;
	if (ConverterMode == EventTags::Converter::EnergyToMatter) ConverterMode = EventTags::Converter::ItemToMatter;
	if (ConverterMode == EventTags::Converter::MatterToEnergy) ConverterMode = EventTags::Converter::ItemToEnergy;
}

void UTSA_ResourceManagerComp::OnConverterRemoveItem(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	if (SlotIndex == 0)ItemInConverter = nullptr;
	if (ConverterMode == EventTags::Converter::ItemToMatter) ConverterMode = EventTags::Converter::EnergyToMatter;
	if (ConverterMode == EventTags::Converter::ItemToEnergy) ConverterMode = EventTags::Converter::MatterToEnergy;
}

void UTSA_ResourceManagerComp::OnPrinterAddItem(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	if (SlotIndex == 0)ItemInPrinter = Item;
}

void UTSA_ResourceManagerComp::OnPrinterRemoveItem(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	if (SlotIndex == 0)ItemInPrinter = nullptr;
}

