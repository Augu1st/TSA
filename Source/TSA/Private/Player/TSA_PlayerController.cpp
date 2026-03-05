// Dark Trace Studio Works


#include "Player/TSA_PlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "UI/HUD/TSA_HUD.h"
#include "GameFramework/Character.h"


void ATSA_PlayerController::BeginPlay()
{
	Super::BeginPlay();
	
	InitHUD();
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
}

void ATSA_PlayerController::InitHUD()
{
	if (GetHUD())
	{
		HUD = Cast<ATSA_HUD>(GetHUD());
		if (!IsValid(HUD)) return;
	}
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
	UE_LOG(LogTemp, Log, TEXT("Primary Interact"));
}
