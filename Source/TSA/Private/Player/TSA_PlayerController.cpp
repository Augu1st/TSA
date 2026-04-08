// Dark Trace Studio Works

#include "Player/TSA_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "TSA_GameplayTags.h"
#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "UI/HUD/TSA_HUD.h"
#include "GameFramework/Character.h"
#include "TSA/TSA.h"
#include "Interaction/TSA_InteractComponent.h"
#include "Items/TSA_InventoryItem.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "UI/Inventory/TSA_InventoryBase.h"
#include "UI/Inventory/Spatial/TSA_InventoryGrid.h"
#include "UI/Inventory/Spatial/TSA_SpatialInventory.h"

ATSA_PlayerController::ATSA_PlayerController()
{
	
}

void ATSA_PlayerController::OpenContainerInventory(UTSA_InventoryComponent* ContainerInventory)
{
	HUD = Cast<ATSA_HUD>(GetHUD());
	HUD-> OpenContainer(ContainerInventory);
}

void ATSA_PlayerController::RequestPickUpItem(UTSA_ItemComponent* ItemComponent)
{
	if (HasAuthority()) 
		Server_PickUpItem_Implementation(ItemComponent);
	else 
		Server_PickUpItem(ItemComponent);
}

void ATSA_PlayerController::RequestAutoAddItem(UTSA_InventoryComponent* SourceComp, int32 SourceIndex)
{
	if (HasAuthority())
		Server_AutoAddItem_Implementation(SourceComp, SourceIndex);
	else
		Server_AutoAddItem(SourceComp, SourceIndex);
	
}

void ATSA_PlayerController::RequestMoveItem(UTSA_InventoryComponent* SourceComp, int32 SourceIndex,
											UTSA_InventoryComponent* TargetComp, int32 TargetIndex)
{
	if (HasAuthority())
		Server_MoveItem_Implementation(SourceComp, SourceIndex, TargetComp, TargetIndex);
	else
		Server_MoveItem(SourceComp, SourceIndex, TargetComp, TargetIndex);
	
}

void ATSA_PlayerController::RequestDropItem(UTSA_InventoryComponent* SourceComp, int32 SlotIndex)
{
	if (HasAuthority())
		Server_DropItem_Implementation(SourceComp, SlotIndex);
	else
		Server_DropItem(SourceComp, SlotIndex);
}

void ATSA_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	SetShowMouseCursor(true);
}

void ATSA_PlayerController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);
	if (!IsValid(HUD))
	{
		HUD = Cast<ATSA_HUD>(GetHUD()); 
	}
	if (HUD) HUD->InitAttributesBindings();
}

void ATSA_PlayerController::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	if (!IsValid(HUD))
	{
		HUD = Cast<ATSA_HUD>(GetHUD()); 
	}
	HUD->InitAttributesBindings();
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
	EnhancedInputComponent->BindAction(AttributeMenuAction,ETriggerEvent::Started,this,&ATSA_PlayerController::ToggleAttributeMenu);
}

void ATSA_PlayerController::Server_PickUpItem_Implementation(UTSA_ItemComponent* ItemComponent)
{
	ATSA_AgentCharacter* PlayerCharacter = Cast<ATSA_AgentCharacter>(GetPawn());
	if (IsValid(PlayerCharacter))
	{
		PlayerCharacter->PickUpItem(ItemComponent);
	}
}

bool ATSA_PlayerController::Server_PickUpItem_Validate(UTSA_ItemComponent* ItemComponent)
{
	return ItemComponent!=nullptr;
}

void ATSA_PlayerController::Server_AutoAddItem_Implementation(UTSA_InventoryComponent* SourceComp, int32 SourceIndex)
{
	UTSA_InventoryItem* Item = SourceComp->GetItemAtIndex(SourceIndex);
	if (IsValid(Item))
	{
		ATSA_AgentCharacter* PlayerCharacter = Cast<ATSA_AgentCharacter>(GetPawn());
		if (PlayerCharacter) PlayerCharacter->PickUpItemInInventory(Item);
		FTSA_ItemManifest& ItemManifest = Item->GetItemManifestMutable();
		if (ItemManifest.StackCount == 0)
		{
			SourceComp->RemoveItem(Item,SourceIndex);
		}
	}
}

bool ATSA_PlayerController::Server_AutoAddItem_Validate(UTSA_InventoryComponent* SourceComp, int32 SourceIndex)
{
	return SourceComp != nullptr && SourceIndex >= 0;
}

void ATSA_PlayerController::Server_MoveItem_Implementation(UTSA_InventoryComponent* SourceComp, int32 SourceIndex,
                                                           UTSA_InventoryComponent* TargetComp, int32 TargetIndex)
{
	SourceComp->MoveItem(SourceIndex, TargetComp, TargetIndex);
}

bool ATSA_PlayerController::Server_MoveItem_Validate(UTSA_InventoryComponent* SourceComp, int32 SourceIndex,
	UTSA_InventoryComponent* TargetComp, int32 TargetIndex)
{
	return SourceComp != nullptr && TargetComp != nullptr && SourceIndex >= 0 && TargetIndex >= 0;
}

void ATSA_PlayerController::ToggleAttributeMenu()
{
	if (GetHUD())
	{	
		HUD = Cast<ATSA_HUD>(GetHUD());
		HUD->ToggleAttributeMenu();
	}
}


void ATSA_PlayerController::Server_DropItem_Implementation(UTSA_InventoryComponent* SourceComp, int32 SlotIndex)
{
	UE_LOG(LogTSA, Warning, TEXT("Server_DropItem_Implementation"))
	SourceComp->DropItemIntoWorld(SlotIndex);
}

bool ATSA_PlayerController::Server_DropItem_Validate(UTSA_InventoryComponent* SourceComp, int32 SlotIndex)
{
	return SourceComp != nullptr && SlotIndex >= 0;
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
	if (!GetHUD())return;
	HUD = Cast<ATSA_HUD>(GetHUD());
	HUD->ToggleInventory();
	// 获取交互组件
	UTSA_InteractComponent* InteractComp = nullptr;
	if (IsValid(GetCharacter()))
	{
		InteractComp = GetCharacter()->FindComponentByClass<UTSA_InteractComponent>();
	}
	
	if (HUD->IsInventoryOpen())
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
}

void ATSA_PlayerController::SetGameInputMode()
{
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);

}