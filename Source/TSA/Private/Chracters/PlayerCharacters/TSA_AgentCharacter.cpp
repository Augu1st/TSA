// Dark Trace Studio Works

#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "TSA/TSA.h"
#include "TSA_GameplayTags.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Interaction/TSA_InteractComponent.h"
#include "Items/Component/TSA_ItemComponent.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "Utils/TSA_ItemUtils.h"


// Sets default values
ATSA_AgentCharacter::ATSA_AgentCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
	
	InitMovement();
	InitCameraAndArm();
	InitInteractComponent();
	InitInventoryComponents();
}

void ATSA_AgentCharacter::PickUpItem(UTSA_ItemComponent* ItemComponent)
{
	const FGameplayTag& ItemCategory = UTSA_ItemUtils::GetItemCategoryFromItemComp(ItemComponent);
	FInstancedStruct& ItemManifestStruct = ItemComponent->GetItemManifestStruct();
	// 尝试在对应仓库添加
	if (InventoryComponentMap.Contains(ItemCategory) && InventoryComponentMap[ItemCategory]->TryAddItem(ItemManifestStruct))
	{
		if (ItemManifestStruct.Get<FTSA_ItemManifestBase>().StackCount == 0) ItemComponent->PickUp();
		return;
	}
	
	// 尝试在通用仓库添加
	if (InventoryComponentMap.Contains(ItemTags::Category::General))
	{
		if (InventoryComponentMap[ItemTags::Category::General]->TryAddItem(ItemManifestStruct))
		{
			if (ItemManifestStruct.Get<FTSA_ItemManifestBase>().StackCount == 0) ItemComponent->PickUp();
			return;
		}
	}
	
}

UTSA_InventoryComponent* ATSA_AgentCharacter::GetInventoryCompByCategory(const FGameplayTag& ItemCategory)
{
	if (InventoryComponentMap.Contains(ItemCategory) == false)
	{
		UE_LOG(LogTSA, Warning, TEXT("%s : InventoryComponentMap does not contain %s"), *GetName(), *ItemCategory.ToString());
		return nullptr;
	}
	return InventoryComponentMap[ItemCategory];
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

void ATSA_AgentCharacter::InitInventoryComponents()
{
	
	EquipmentInventoryComp = CreateDefaultSubobject<UTSA_InventoryComponent>("EquipmentInventory");
	InventoryComponentMap.Add(ItemTags::Category::Equipment, EquipmentInventoryComp.Get());
	
	PropInventoryComp = CreateDefaultSubobject<UTSA_InventoryComponent>("PropInventory");
	InventoryComponentMap.Add(ItemTags::Category::Prop, PropInventoryComp.Get());
	
	GeneralInventoryComp = CreateDefaultSubobject<UTSA_InventoryComponent>("GeneralInventory");
	InventoryComponentMap.Add(ItemTags::Category::General, GeneralInventoryComp.Get());
}

void ATSA_AgentCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

