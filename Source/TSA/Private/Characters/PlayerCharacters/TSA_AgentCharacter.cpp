// Dark Trace Studio Works

#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"

#include "AbilitySystemComponent.h"
#include "TSA/TSA.h"
#include "TSA_GameplayTags.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interaction/TSA_InteractComponent.h"
#include "Items/TSA_InventoryItem.h"
#include "Items/Component/TSA_ItemComponent.h"
#include "Net/UnrealNetwork.h"
#include "Player/TSA_PlayerController.h"
#include "Player/TSA_PlayerState.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "Utils/TSA_ItemUtils.h"


// Sets default values
ATSA_AgentCharacter::ATSA_AgentCharacter()
{
	PrimaryActorTick.bCanEverTick = true;
	bReplicates = true;
	
	InitMovement();
	InitCameraAndArm();
	InitInteractComponent();
	InitInventoryComponents();
}

void ATSA_AgentCharacter::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATSA_AgentCharacter, EquipmentInventoryComp);
	DOREPLIFETIME(ATSA_AgentCharacter, PropInventoryComp);
	DOREPLIFETIME(ATSA_AgentCharacter, GeneralInventoryComp);
}

void ATSA_AgentCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	InitAbilitySystemInfo();
}

void ATSA_AgentCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	
	InitAbilitySystemInfo();
}

void ATSA_AgentCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	
	UpdateLookAtMouse();
}

void ATSA_AgentCharacter::PickUpItem(UTSA_ItemComponent* ItemComponent)
{
	const FGameplayTag& ItemCategory = UTSA_ItemUtils::GetItemCategoryFromItemComp(ItemComponent);
	FInstancedStruct& ItemManifestStruct = ItemComponent->GetItemManifestStruct();
	// 尝试在对应仓库添加
	if (UTSA_InventoryComponent* InventoryComp = GetInventoryCompByCategory(ItemCategory))
	{
		InventoryComp->TryAddItem(ItemManifestStruct);
		if (ItemManifestStruct.Get<FTSA_ItemManifestBase>().StackCount == 0) ItemComponent->PickUp();
		return;
	}
	
	// 尝试在通用仓库添加
	if (IsValid(GeneralInventoryComp))
	{
		if (GeneralInventoryComp->TryAddItem(ItemManifestStruct))
		{
			if (ItemManifestStruct.Get<FTSA_ItemManifestBase>().StackCount == 0) ItemComponent->PickUp();
		}
	}
}

void ATSA_AgentCharacter::PickUpItemInInventory(UTSA_InventoryItem* Item)
{
	if (!IsValid(Item)) return;
	
	const FGameplayTag& ItemCategory = UTSA_ItemUtils::GetItemCategoryFromItem(Item);
	FInstancedStruct& ItemManifestStruct = Item->GetItemManifestStruct();
	// 尝试在对应仓库添加
	if(UTSA_InventoryComponent* InventoryComp = GetInventoryCompByCategory(ItemCategory))
	{
		InventoryComp->TryAddItem(ItemManifestStruct);
		if (ItemManifestStruct.Get<FTSA_ItemManifestBase>().StackCount == 0) return;
	}
	// 尝试在通用仓库添加
	if (IsValid(GeneralInventoryComp))
	{
		GeneralInventoryComp->TryAddItem(ItemManifestStruct);
	}
}

UTSA_InventoryComponent* ATSA_AgentCharacter::GetInventoryCompByCategory(const FGameplayTag& ItemCategory)
{
	for (UTSA_InventoryComponent* InventoryComp : InventoryComponents)
	{
		if (!IsValid(InventoryComp)) continue;
		if (InventoryComp->MatchItemCategory(ItemCategory)) return InventoryComp;
	}
	UE_LOG(LogTSA, Warning, TEXT("%s : InventoryComponentMap does not contain %s"), *GetName(), *ItemCategory.ToString());
	return nullptr;
}

void ATSA_AgentCharacter::BeginPlay()
{
	Super::BeginPlay();
}

void ATSA_AgentCharacter::UpdateLookAtMouse()
{
	APlayerController* PC = Cast<APlayerController>(GetController());
	if (IsValid(PC))
	{
		FVector MouseWorldLoc, MouseWorldDir;
		if (PC->DeprojectMousePositionToWorld(MouseWorldLoc, MouseWorldDir))
		{
			// 创建一个位于角色脚下的水平面
			FPlane GroundPlane(GetActorLocation(), FVector::UpVector);
        
			// 计算射线与平面的交点
			FVector IntersectionPoint;
			if (FMath::SegmentPlaneIntersection(MouseWorldLoc, MouseWorldLoc + MouseWorldDir * 10000.0f, GroundPlane, IntersectionPoint))
			{
				FVector LookDir = IntersectionPoint - GetActorLocation();
				LookDir.Z = 0.0f;
				SetActorRotation(LookDir.Rotation());
			}
		}
	}
}


void ATSA_AgentCharacter::InitMovement()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	GetCharacterMovement()->bOrientRotationToMovement = false;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 540.0f, 0.0f);
	GetCharacterMovement()->MaxWalkSpeed = 500.0f;// TODO:从属性获取
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

void ATSA_AgentCharacter::InitInventoryComponents()
{
	if (!EquipmentInventoryComp)
		EquipmentInventoryComp = CreateDefaultSubobject<UTSA_InventoryComponent>("EquipmentInventory");
	
	if (!PropInventoryComp)
		PropInventoryComp = CreateDefaultSubobject<UTSA_InventoryComponent>("PropInventory");
	
	if (!GeneralInventoryComp)
		GeneralInventoryComp = CreateDefaultSubobject<UTSA_InventoryComponent>("GeneralInventory");
	
	InventoryComponents.Add(EquipmentInventoryComp);
	InventoryComponents.Add(PropInventoryComp);
	InventoryComponents.Add(GeneralInventoryComp);
}

void ATSA_AgentCharacter::InitAbilitySystemInfo()
{
	ATSA_PlayerState* PS = GetPlayerState<ATSA_PlayerState>();
	check(PS);
	PS->GetAbilitySystemComponent()->InitAbilityActorInfo(PS, this);
	AbilitySystemComponent = PS->GetAbilitySystemComponent();
}
