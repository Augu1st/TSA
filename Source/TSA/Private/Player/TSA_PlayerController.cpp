// Dark Trace Studio Works

#include "Player/TSA_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "UI/HUD/TSA_HUD.h"
#include "GameFramework/Character.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "TSA/TSA.h"
#include "Interaction/TSA_InteractComponent.h"

ATSA_PlayerController::ATSA_PlayerController()
{
	InitHUD();
	InitInventoryComponents();
}

void ATSA_PlayerController::BeginPlay()
{
	Super::BeginPlay();
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

void ATSA_PlayerController::InitHUD()
{
	if (GetHUD())
	{
		HUD = Cast<ATSA_HUD>(GetHUD());
	}
}

void ATSA_PlayerController::InitInventoryComponents()
{
	if (InventoryComponentClass!= nullptr)
	{
		UE_LOG(LogTSA, Warning, TEXT("%s : InventoryComponentClass is not set"), *GetName());
		return;
	}
	MainInventoryComp = CreateDefaultSubobject<UTSA_InventoryComponent>("MainInventoryComp");
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
	if (!IsValid(MainInventoryComp)) return;
	
	MainInventoryComp->ToggleInventory();
	if (MainInventoryComp->IsInventoryVisible())
	{
		SetCursorInputMode();
	}
	else
	{
		SetGameInputMode();
	}
}

void ATSA_PlayerController::SetCursorInputMode()
{
	FInputModeGameAndUI InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = true;
}

void ATSA_PlayerController::SetGameInputMode()
{
	FInputModeGameOnly InputMode;
	SetInputMode(InputMode);
	bShowMouseCursor = false;
}