// Dark Trace Studio Works

#include "Player/TSA_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "TSA_GameplayTags.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "UI/HUD/TSA_HUD.h"
#include "GameFramework/Character.h"
#include "TSA/TSA.h"
#include "Interaction/TSA_InteractComponent.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "UI/Inventory/TSA_InventoryBase.h"
#include "UI/Inventory/Spatial/TSA_InventoryGrid.h"
#include "UI/Inventory/Spatial/TSA_SpatialInventory.h"

ATSA_PlayerController::ATSA_PlayerController()
{
	InitHUD();
}

void ATSA_PlayerController::OpenContainerInventory(UTSA_InventoryComponent* ContainerInventory)
{
	// 如果已经打开了容器，直接返回
	if (CurrentContainer.IsValid()) return;
	
	CurrentContainer = ContainerInventory;
	
	UTSA_SpatialInventory* SpatialInventory = Cast<UTSA_SpatialInventory>(GetInventoryMenu());
	SpatialInventory->Grid_Container->InitializeGrid(ContainerInventory);
	SpatialInventory->Grid_Container->SetVisibility(ESlateVisibility::Visible);
	
	InteractWithInventory();
}

void ATSA_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	InitializeInventoryMenu();
}

void ATSA_PlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	UEnhancedInputLocalPlayerSubsystem* InputLocalPlayerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	if (!IsValid(InputLocalPlayerSubsystem)) return;
	
	for (const auto& Context : InputMappingContexts)
	{
		InputLocalPlayerSubsystem->AddMappingContext(Context,0);
	}
	
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if (!IsValid(EnhancedInputComponent)) return;
	
	EnhancedInputComponent->BindAction(MoveAction,ETriggerEvent::Triggered,this,&ATSA_PlayerController::Move);
	EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Started,this,&ATSA_PlayerController::Jump);
	EnhancedInputComponent->BindAction(JumpAction,ETriggerEvent::Completed,this,&ATSA_PlayerController::StopJumping);
	
	EnhancedInputComponent->BindAction(PrimaryInteractAction,ETriggerEvent::Started,this,&ATSA_PlayerController::PrimaryInteract);
	
	EnhancedInputComponent->BindAction(InventoryAction,ETriggerEvent::Started,this,&ATSA_PlayerController::InteractWithInventory);
}

void ATSA_PlayerController::InitializeInventoryMenu()
{
	ATSA_AgentCharacter* AgentCharacter = Cast<ATSA_AgentCharacter>(GetCharacter());
	UTSA_InventoryComponent* EquipmentInventoryComp = AgentCharacter->GetInventoryCompByCategory(ItemTags::Category::Equipment);
	UTSA_InventoryComponent* PropInventoryComp = AgentCharacter->GetInventoryCompByCategory(ItemTags::Category::Prop);
	UTSA_InventoryComponent* GeneralInventoryComp = AgentCharacter->GetInventoryCompByCategory(ItemTags::Category::General);
	
	UTSA_SpatialInventory* SpatialInventory = Cast<UTSA_SpatialInventory>(GetInventoryMenu());
	
	SpatialInventory->Grid_Equipment->InitializeGrid(EquipmentInventoryComp);
	SpatialInventory->Grid_Prop->InitializeGrid(PropInventoryComp);
	SpatialInventory->Grid_General->InitializeGrid(GeneralInventoryComp);
	SpatialInventory->Grid_Container->SetVisibility(ESlateVisibility::Collapsed);
}

UTSA_InventoryBase* ATSA_PlayerController::GetInventoryMenu()
{
	if (!IsValid(InventoryMenu))
	{
		ConstructInventory();
	}
	return InventoryMenu;
}

void ATSA_PlayerController::ToggleInventory()
{
	if (GetInventoryMenu())
	{
		if (bInventoryMenuOpen)
		{
			InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
			ClearContainerGrid();
		}
		else InventoryMenu->SetVisibility(ESlateVisibility::Visible);
		bInventoryMenuOpen = !bInventoryMenuOpen;
	}
}


void ATSA_PlayerController::ClearContainerGrid()
{
	if (!CurrentContainer.IsValid()) return;
	
	if (UTSA_SpatialInventory* SpatialInventory = Cast<UTSA_SpatialInventory>(GetInventoryMenu()))
	{
		SpatialInventory->Grid_Container->SetVisibility(ESlateVisibility::Collapsed);
		SpatialInventory->Grid_Container->ClearGrid();
	}
	CurrentContainer = nullptr;
}

void ATSA_PlayerController::InitHUD()
{
	if (GetHUD())
	{
		HUD = Cast<ATSA_HUD>(GetHUD());
	}
}

void ATSA_PlayerController::ConstructInventory()
{
	if (!IsValid(InventoryMenuClass)) return;
	InventoryMenu = CreateWidget<UTSA_InventoryBase>(GetWorld(),InventoryMenuClass);
	InventoryMenu->AddToViewport();
	InventoryMenu->SetVisibility(ESlateVisibility::Collapsed);
}

void ATSA_PlayerController::Move(const FInputActionValue& Value)
{
	APawn* ControlledPawn = Cast<APawn>(GetPawn());
	if (!IsValid(ControlledPawn)) return;
	
	const FVector2D InputAxisVector = Value.Get<FVector2D>();
    const FRotator Rotation = GetControlRotation();
    const FRotator YawRotation(0.f,Rotation.Yaw,0.f);
    
    const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
    const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	
    ControlledPawn -> AddMovementInput(ForwardDirection,InputAxisVector.Y);
	ControlledPawn -> AddMovementInput(RightDirection,InputAxisVector.X);
}

void ATSA_PlayerController::Jump()
{
	if (!IsValid(GetCharacter())) return;
	
	GetCharacter()->Jump();
}

void ATSA_PlayerController::StopJumping()
{
	if (!IsValid(GetCharacter())) return;
	
	GetCharacter()->StopJumping();
}


void ATSA_PlayerController::PrimaryInteract()
{
	if (!IsValid(GetCharacter())) return;
	UTSA_InteractComponent* InteractComponent = GetCharacter()->FindComponentByClass<UTSA_InteractComponent>();
	
	if (!IsValid(InteractComponent))
	{
		UE_LOG(LogTSA, Warning, TEXT("%s: Owning Character has no InteractComponent"), *GetName());
		return;
	}
	
	InteractComponent->PrimaryInteract();
}

void ATSA_PlayerController::InteractWithInventory()
{
	ToggleInventory();
	
	// 获取交互组件
	UTSA_InteractComponent* InteractComp = nullptr;
	if (IsValid(GetCharacter()))
	{
		InteractComp = GetCharacter()->FindComponentByClass<UTSA_InteractComponent>();
	}
	
	if (IsInventoryOpen())
	{
		SetCursorInputMode();
		if (IsValid(InteractComp)) InteractComp->SetInteractionEnabled(false);
	}
	else
	{
		SetGameInputMode();
		if (IsValid(InteractComp)) InteractComp->SetInteractionEnabled(true);
	}
}

void ATSA_PlayerController::SetCursorInputMode()
{
	FInputModeGameAndUI InputMode;
	// 不锁定鼠标在屏幕内（PC游戏标准配置）
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	// 捕获鼠标时不要隐藏它
	InputMode.SetHideCursorDuringCapture(false); 
	
	SetInputMode(InputMode);
	bShowMouseCursor = true;
}

void ATSA_PlayerController::SetGameInputMode()
{
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;
}