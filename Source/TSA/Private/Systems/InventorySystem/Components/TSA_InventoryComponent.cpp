// Dark Trace Studio Works


#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"

#include "Systems/MessageSystem/TSA_MessageUtils.h"
#include "Systems/MessageSystem/TSA_UIMessageSubsystem.h"
#include "UI/Inventory/TSA_InventoryBase.h"
#include "Items/Component/TSA_ItemComponent.h"
#include "Net/UnrealNetwork.h"

UTSA_InventoryComponent::UTSA_InventoryComponent()
{
	PrimaryComponentTick.bCanEverTick = false;

	SetIsReplicatedByDefault(true);
	bReplicateUsingRegisteredSubObjectList = true;
}

void UTSA_InventoryComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ThisClass,InventoryList);
}

void UTSA_InventoryComponent::TryAddItem(UTSA_ItemComponent* ItemComponent)
{
	FTSA_SlotAvailabilityResult Result = GetInventoryMenu()->HasRoomForItem(ItemComponent);
	
	// 情况1： 背包已满
	if (Result.TotalRoomToFill == 0)
	{
		UTSA_UIMessageSubsystem* MsgSys = UTSA_MessageUtils::GetUIMessageSubsystem(GetOwner());
		MsgSys->BroadcastUIMessage(FText::FromString("背包空间不足!"));// TODO: 文本映射
		return;
	}
	
	// 情况2： 背包已存在相同物品
	if (Result.Item.IsValid() && Result.bStackable)
	{
		Server_AddStacksToItem(ItemComponent,Result.TotalRoomToFill,Result.Remainder);
	}
	// 情况3： 背包无相同物品 或 物品不可堆叠
	else
	{
		Server_AddNewItem(ItemComponent,Result.bStackable ? Result.TotalRoomToFill : 0);
	}
	
}

void UTSA_InventoryComponent::Server_AddNewItem_Implementation(UTSA_ItemComponent* ItemComponent, int32 StackCount)
{
	UTSA_InventoryItem* NewItem = InventoryList.AddEntry(ItemComponent);
}

void UTSA_InventoryComponent::Server_AddStacksToItem_Implementation(UTSA_ItemComponent* ItemComponent, int32 StackCount,
	int32 Remainder)
{
	
}

void UTSA_InventoryComponent::AddRepSubObj(UObject* SubObj)
{
	if (IsUsingRegisteredSubObjectList() && IsReadyForReplication() && SubObj)
	{
		AddReplicatedSubObject(SubObj);
	}
}

void UTSA_InventoryComponent::ToggleInventory()
{
	if (GetInventoryMenu())
	{
		if (bInventoryMenuOpen) InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
		else InventoryMenu->SetVisibility(ESlateVisibility::Visible);
		bInventoryMenuOpen = !bInventoryMenuOpen;
	}
}

UTSA_InventoryBase* UTSA_InventoryComponent::GetInventoryMenu()
{
	if (!IsValid(InventoryMenu))
	{
		ConstructInventory();
	}
	return InventoryMenu;
}

void UTSA_InventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UTSA_InventoryComponent::ConstructInventory()
{
	if (!IsValid(InventoryMenuClass)) return;
	InventoryMenu = CreateWidget<UTSA_InventoryBase>(GetOwner()->GetWorld(),InventoryMenuClass);
	InventoryMenu->AddToViewport();
	InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
}


