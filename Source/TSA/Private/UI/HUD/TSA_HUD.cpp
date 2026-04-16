// Dark Trace Studio Works


#include "UI/HUD/TSA_HUD.h"

#include "TSA_GameplayTags.h"
#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Player/TSA_PlayerController.h"
#include "Player/TSA_PlayerState.h"
#include "UI/AttributeMenu/TSA_AttributeMenuController.h"
#include "UI/AttributeMenu/TSA_AttributeMenu.h"
#include "UI/HUD/TSA_HUDWidget.h"
#include "UI/Inventory/Spatial/TSA_InventoryGrid.h"
#include "UI/Inventory/Spatial/TSA_SpatialInventory.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "UI/BondMenu/TSA_BondMenuController.h"
#include "UI/BondMenu/TSA_BondMenu.h"
#include "UI/HUD/TSA_DamageTextComponent.h"
#include "UI/Inventory/SlottedItems/TSA_ContextMenu.h"
#include "UI/Inventory/Spatial/TSA_QuickGrid.h"


ATSA_HUD::ATSA_HUD()
{
}

void ATSA_HUD::BeginPlay()
{
	Super::BeginPlay();

}

void ATSA_HUD::SpawnDamageText(float Damage, ACharacter* TargetCharacter)
{
	//IsValid会检查对象是否处于即将销毁状态
	if (IsValid(TargetCharacter) && DamageTextComponentClass)
	{
		UTSA_DamageTextComponent* DamageText = NewObject<UTSA_DamageTextComponent>(
			TargetCharacter,//外部对象
			DamageTextComponentClass);//生成的对象类
		DamageText->RegisterComponent();//注册组件，使得引擎可以管理
		DamageText->AttachToComponent(TargetCharacter->GetRootComponent(),FAttachmentTransformRules::KeepRelativeTransform);//依附于外部对象
		DamageText->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);//再脱离外部对象
					DamageText->SetDamageText(Damage);//设置文本内容
	}
}

void ATSA_HUD::CreateHUDWidget()
{
	if (!IsValid(HUDWidgetClass))return;
	HUDWidget = CreateWidget<UTSA_HUDWidget>(GetWorld(),HUDWidgetClass);
	if (IsValid(HUDWidget))
	{
		HUDWidget->AddToViewport(0);
	}
	OnAttributeChanged.AddDynamic(HUDWidget,&UTSA_HUDWidget::UpdateAttribute);
}

void ATSA_HUD::InitAttributesBindings()
{
	APlayerController* PC = GetOwningPlayerController();
	if (!PC) return;

	ATSA_PlayerState* PS = PC->GetPlayerState<ATSA_PlayerState>();
	if (!PS) return;

	ASC = Cast<UTSA_AbilitySystemComponent>(PS->GetAbilitySystemComponent());
	if (!ASC.IsValid()) return;
	
	for (const FTSA_AttributeInfo& Info : AttributeData->AttributeInformation)
	{
		ASC->GetGameplayAttributeValueChangeDelegate(Info.Attribute).AddUObject(
			this,
			&ATSA_HUD::OnAnyAttributeChange,
			Info.AttributeTag
		);
	}
	CreateHUDWidget();
	BroadcastInitAttributes();
	GetAttributeMenu();
	GetAttributeMenuController()->BroadcastInitAttributes(ASC.Get());
	GetBondMenu();
}

void ATSA_HUD::BroadcastInitAttributes()
{
	if (!ASC.IsValid()) return;
	
	for (const FTSA_AttributeInfo& Info : AttributeData->AttributeInformation)
	{
		float Value = ASC->GetNumericAttribute(Info.Attribute);
		OnAttributeChanged.Broadcast(Info.AttributeTag, Value);
	}
}

void ATSA_HUD::ToggleInventory()
{
	if (GetInventoryMenu())
	{
		if (!bInitInventoryMenu)
		{
			InitializeInventoryMenu();
			ATSA_AgentCharacter* AgentCharacter = Cast<ATSA_AgentCharacter>(GetOwningPlayerController()->GetPawn());
			if (AgentCharacter && AgentCharacter->GetASC())
			{
				BroadcastInitAttributes();
			}
			bInitInventoryMenu = true;
		}
		if (bInventoryMenuOpen)
		{
			InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
			ClearContainerGrid();
			if (ContextMenu) ContextMenu->CloseMenu();
		}
		else
		{
			InventoryMenu->SetVisibility(ESlateVisibility::Visible);
		}
		bInventoryMenuOpen = !bInventoryMenuOpen;
	}
}

void ATSA_HUD::OpenContainer(UTSA_InventoryComponent* ContainerInventory)
{
	if (CurrentContainer.IsValid()) return;
	
	CurrentContainer = ContainerInventory;
	
	ATSA_PlayerController* PC = Cast<ATSA_PlayerController>(GetOwningPlayerController());
	if (PC)PC->InteractWithInventory();
	
	UTSA_SpatialInventory* SpatialInventory = Cast<UTSA_SpatialInventory>(GetInventoryMenu());
	SpatialInventory->Grid_Container->InitializeGrid(ContainerInventory);
	SpatialInventory->Grid_Container->SetVisibility(ESlateVisibility::Visible);	
}

UTSA_AttributeMenuController* ATSA_HUD::GetAttributeMenuController()
{
	if (!AttributeMenuController)
	{
		AttributeMenuController = NewObject<UTSA_AttributeMenuController>(this,AttributeMenuControllerClass,TEXT("AttributeMenuController"));
		if (ASC.IsValid())
		{
			AttributeMenuController->InitAttributesBindings(ASC.Get());
		}
	}
	return AttributeMenuController;
}

UTSA_AttributeMenu* ATSA_HUD::GetAttributeMenu()
{
	if (!AttributeMenu)
	{
		AttributeMenu = CreateWidget<UTSA_AttributeMenu>(GetWorld(), AttributeMenuClass);
		AttributeMenu->AddToViewport(5);
		AttributeMenu->SetVisibility(ESlateVisibility::Collapsed);
		AttributeMenu->InitAttributeMenu(GetAttributeMenuController());
	}
	return AttributeMenu;
}

void ATSA_HUD::ToggleAttributeMenu()
{
	if (!bAttributeMenuOpen)
	{
		GetAttributeMenu()->SetVisibility(ESlateVisibility::SelfHitTestInvisible);
		bAttributeMenuOpen = true;
	}
	else
	{
		GetAttributeMenu()->SetVisibility(ESlateVisibility::Collapsed);
		bAttributeMenuOpen = false;
	}
}

UTSA_BondMenuController* ATSA_HUD::GetBondMenuController()
{
	if (!BondMenuController)
	{
		BondMenuController = NewObject<UTSA_BondMenuController>(this,BondMenuControllerClass);
		ATSA_AgentCharacter* AgentCharacter = Cast<ATSA_AgentCharacter>(GetOwningPlayerController()->GetPawn());
		if (AgentCharacter)BondMenuController->InitBondDelegate(AgentCharacter);
	}
	return BondMenuController;
}

UTSA_BondMenu* ATSA_HUD::GetBondMenu()
{
	if (!BondMenu)
	{
		BondMenu = CreateWidget<UTSA_BondMenu>(GetWorld(), BondMenuClass);
		BondMenu->InitBondMenu(GetBondMenuController());
		BondMenu->AddToViewport(5);
	}
	return BondMenu;
}

void ATSA_HUD::OnAnyAttributeChange(const FOnAttributeChangeData& Data, FGameplayTag AttributeTag)
{
	OnAttributeChanged.Broadcast(AttributeTag, Data.NewValue);
}

UTSA_InventoryBase* ATSA_HUD::GetInventoryMenu()
{
	if (!IsValid(InventoryMenu))
	{
		ConstructInventory();
	}
	return InventoryMenu;
}

void ATSA_HUD::ConstructInventory()
{
	if (!IsValid(InventoryMenuClass)) return;
	InventoryMenu = CreateWidget<UTSA_SpatialInventory>(GetWorld(),InventoryMenuClass);
	InventoryMenu->AddToViewport(1);
	InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
	
	UTSA_SpatialInventory* SpatialInventory = Cast<UTSA_SpatialInventory>(InventoryMenu);
	if (SpatialInventory)
	{
		OnAttributeChanged.AddDynamic(SpatialInventory, &UTSA_SpatialInventory::UpdateAttribute);
	}
}

void ATSA_HUD::InitializeInventoryMenu()
{
	ATSA_AgentCharacter* AgentCharacter = Cast<ATSA_AgentCharacter>(GetOwningPlayerController()->GetPawn());
	UTSA_InventoryComponent* EquipmentInventoryComp = AgentCharacter->GetInventoryCompByCategory(ItemTags::Category::Equipment);
	UTSA_InventoryComponent* PropInventoryComp = AgentCharacter->GetInventoryCompByCategory(ItemTags::Category::Prop);
	UTSA_InventoryComponent* GeneralInventoryComp = AgentCharacter->GetInventoryCompByCategory(ItemTags::Category::General);
	UTSA_InventoryComponent* WeaponInventoryComp = AgentCharacter->GetEquipmentInventoryByCategory(ItemTags::Category::Equipment_Weapon);
	UTSA_InventoryComponent* ArmorInventoryComp = AgentCharacter->GetEquipmentInventoryByCategory(ItemTags::Category::Equipment_Armor);
	UTSA_InventoryComponent* ModuleInventoryComp = AgentCharacter->GetEquipmentInventoryByCategory(ItemTags::Category::Equipment_Module);
	UTSA_InventoryComponent* ConverterInventoryComp = AgentCharacter->GetConverterInventory();
	UTSA_InventoryComponent* PrinterInventoryComp = AgentCharacter->GetPrinterInventory();
	UTSA_InventoryComponent* ConnectorInventoryComp = AgentCharacter->GetConnectorInventory();
	
	UTSA_SpatialInventory* SpatialInventory = Cast<UTSA_SpatialInventory>(GetInventoryMenu());
	
	SpatialInventory->Grid_Equipment->InitializeGrid(EquipmentInventoryComp);
	SpatialInventory->Grid_Prop->InitializeGrid(PropInventoryComp);
	SpatialInventory->Grid_General->InitializeGrid(GeneralInventoryComp);
	SpatialInventory->Grid_Weapon->InitializeGrid(WeaponInventoryComp);
	SpatialInventory->Grid_Armor->InitializeGrid(ArmorInventoryComp);
	SpatialInventory->Grid_Module->InitializeGrid(ModuleInventoryComp);
	SpatialInventory->Grid_Converter->InitializeGrid(ConverterInventoryComp);
	SpatialInventory->Grid_Printer->InitializeGrid(PrinterInventoryComp);
	SpatialInventory->Grid_Connector->InitializeGrid(ConnectorInventoryComp);
	SpatialInventory->Grid_Container->SetVisibility(ESlateVisibility::Collapsed);
}

void ATSA_HUD::ClearContainerGrid()
{
	if (!CurrentContainer.IsValid()) return;
	
	if (UTSA_SpatialInventory* SpatialInventory = Cast<UTSA_SpatialInventory>(GetInventoryMenu()))
	{
		SpatialInventory->Grid_Container->SetVisibility(ESlateVisibility::Collapsed);
		SpatialInventory->Grid_Container->ClearGrid();
	}
	CurrentContainer = nullptr;
}
