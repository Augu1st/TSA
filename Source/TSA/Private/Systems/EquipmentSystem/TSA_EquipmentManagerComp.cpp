// Dark Trace Studio Works


#include "Systems/EquipmentSystem/TSA_EquipmentManagerComp.h"

#include "AbilitySystemComponent.h"
#include "TSA_GameplayTags.h"
#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Items/DataAssets/TSA_ItemDataAsset.h"
#include "Items/DataAssets/TSA_ItemFragment.h"
#include "Items/DataTable/TSA_ItemData.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "Utils/TSA_ItemUtils.h"

UTSA_EquipmentManagerComp::UTSA_EquipmentManagerComp()
{
	PrimaryComponentTick.bCanEverTick = false;
	
}

// Called when the game starts
void UTSA_EquipmentManagerComp::BeginPlay()
{
	Super::BeginPlay();
	//获取装备背包组件
	ATSA_AgentCharacter* Agent = Cast<ATSA_AgentCharacter>(GetOwner());
	if (!Agent) return;
	UTSA_InventoryComponent* WeaponInventoryComp = Agent->GetEquipmentInventoryByCategory(ItemTags::Category::Equipment_Weapon);
	UTSA_InventoryComponent* ArmorInventoryComp = Agent->GetEquipmentInventoryByCategory(ItemTags::Category::Equipment_Armor);
	UTSA_InventoryComponent* ModuleInventoryComp = Agent->GetEquipmentInventoryByCategory(ItemTags::Category::Equipment_Module);
	
	if (WeaponInventoryComp)
	{
		WeaponInventoryComp->OnItemAdded.AddDynamic(this, &UTSA_EquipmentManagerComp::OnWeaponEquipped);
		WeaponInventoryComp->OnItemRemoved.AddDynamic(this, &UTSA_EquipmentManagerComp::OnWeaponUnequipped);
	}
	if (ArmorInventoryComp)
	{
		ArmorInventoryComp->OnItemAdded.AddDynamic(this, &UTSA_EquipmentManagerComp::OnArmorEquipped);
		ArmorInventoryComp->OnItemRemoved.AddDynamic(this, &UTSA_EquipmentManagerComp::OnArmorUnequipped);
	}
	if (ModuleInventoryComp)
	{
		ModuleInventoryComp->OnItemAdded.AddDynamic(this, &UTSA_EquipmentManagerComp::OnModuleEquipped);
		ModuleInventoryComp->OnItemRemoved.AddDynamic(this, &UTSA_EquipmentManagerComp::OnModuleUnequipped);
	}
}

void UTSA_EquipmentManagerComp::OnWeaponEquipped(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	
}

void UTSA_EquipmentManagerComp::OnWeaponUnequipped(UTSA_InventoryItem* Item, int32 SlotIndex)
{
}

void UTSA_EquipmentManagerComp::OnArmorEquipped(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	FTSA_ItemDataRow DataRow;
	UTSA_ItemUtils::GetItemStaticDataFromItem(Item, DataRow);
	if (DataRow.ItemDataAsset)
	{
		ATSA_AgentCharacter* Agent = Cast<ATSA_AgentCharacter>(GetOwner());
		if (!IsValid(Agent)) return;
		UTSA_AbilitySystemComponent* ASC = Agent->GetASC();
		if (const UTSA_AttributeFragment* AttributeFragment = DataRow.ItemDataAsset->FindFragment<UTSA_AttributeFragment>())
		{
			FGameplayEffectSpecHandle EffectSpec =ASC->MakeOutgoingSpec(AttributeFragment->AttributeGEClass,1,ASC->MakeEffectContext());
			ActiveGEHandles.Add(Item, ASC->ApplyGameplayEffectSpecToSelf(*EffectSpec.Data.Get()));
		}
	}
}

void UTSA_EquipmentManagerComp::OnArmorUnequipped(UTSA_InventoryItem* Item, int32 SlotIndex)
{
	FTSA_ItemDataRow DataRow;
	UTSA_ItemUtils::GetItemStaticDataFromItem(Item, DataRow);
	if (DataRow.ItemDataAsset)
	{
		ATSA_AgentCharacter* Agent = Cast<ATSA_AgentCharacter>(GetOwner());
		if (!IsValid(Agent)) return;
		UTSA_AbilitySystemComponent* ASC = Agent->GetASC();
		ASC->RemoveActiveGameplayEffect(ActiveGEHandles[Item]);
		ActiveGEHandles.Remove(Item);
	}
}

void UTSA_EquipmentManagerComp::OnModuleEquipped(UTSA_InventoryItem* Item, int32 SlotIndex)
{
}

void UTSA_EquipmentManagerComp::OnModuleUnequipped(UTSA_InventoryItem* Item, int32 SlotIndex)
{
}


