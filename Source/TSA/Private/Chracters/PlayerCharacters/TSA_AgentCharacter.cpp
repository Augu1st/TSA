// Dark Trace Studio Works


#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interaction/TSA_InteractComponent.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "TSA/TSA.h"


// Sets default values
ATSA_AgentCharacter::ATSA_AgentCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	InitMovement();
	InitCameraAndArm();
	InitInteractComponent();
}

void ATSA_AgentCharacter::InitMovement()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;
}

void ATSA_AgentCharacter::InitCameraAndArm()
{
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>("CameraArm");
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 800.f;
	CameraBoom->bUsePawnControlRotation = false;
	
	//取消悬臂对角色旋转的继承
	CameraBoom->bInheritPitch = false;
	CameraBoom->bInheritYaw = false;
	CameraBoom->bInheritRoll = false;
	
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(CameraBoom);
	CameraBoom->bUsePawnControlRotation = false;
}

void ATSA_AgentCharacter::InitInteractComponent()
{
	InteractComponent = CreateDefaultSubobject<UTSA_InteractComponent>("InteractComponent");
}

void ATSA_AgentCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	
}

