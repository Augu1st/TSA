// Dark Trace Studio Works


#include "Systems/InventorySystem/Containers/TSA_Container.h"

#include "Items/Manifest/TSA_ItemManifest.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "Systems/InventorySystem/Containers/TSA_RandomItemPool.h"
#include "TSA/TSA.h"
#include "TSA_GameplayTags.h"
#include "Net/UnrealNetwork.h"
#include "Player/TSA_PlayerController.h"
#include "Utils/TSA_ItemUtils.h"


ATSA_Container::ATSA_Container()
{
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	InventoryComponent = CreateDefaultSubobject<UTSA_InventoryComponent>(TEXT("InventoryComponent"));
}

void ATSA_Container::PrimaryInteract_Implementation(APlayerController* Interactor)
{
	ATSA_PlayerController* PlayerController = Cast<ATSA_PlayerController>(Interactor);
	if (!IsValid(PlayerController)) return;
	
	if (PlayerController->IsLocalController())
	{
		PlayerController->OpenContainerInventory(InventoryComponent);
	}
}

void ATSA_Container::BeginPlay()
{
	Super::BeginPlay();
	
	// 服务器开局生成物品
	if (HasAuthority())
	{
		Server_SpawnItems_Implementation();
		bIsSpawned =  true;
	}
}

void ATSA_Container::GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);
	DOREPLIFETIME(ATSA_Container, InventoryComponent);
}

void ATSA_Container::Server_SpawnItems_Implementation()
{
	if (ItemPool.IsNull())
	{
		UE_LOG(LogTSA, Error, TEXT("%s:ItemPool is not configured in Blueprint!"), *GetName());
		return;
	}
	
	// 将软引用同步加载到内存中！(这步是魔法)
	UTSA_RandomItemPool* LoadedPool = ItemPool.LoadSynchronous();
	if (!IsValid(LoadedPool))
	{
		UE_LOG(LogTSA, Error, TEXT("%s: Failed to load ItemPool into memory!"), *GetName());
		return;
	}
	
	int32 ItemCount = FMath::RandRange(MinItemCount, MaxItemCount);
	for (int32 i = 0; i < ItemCount; ++i)
	{
		// 每次循环只负责调用单次生成流水线
		GenerateSingleItem(LoadedPool);
	}
}

void ATSA_Container::GenerateSingleItem(UTSA_RandomItemPool* LoadedPool)
{
	FDataTableRowHandle ResultHandle;
	int32 ResultQuantity = 0;
		
	// 第一步：从奖池中抽奖，获得身份证(Handle)和数量
	if (!LoadedPool->RollItemFromTables(ResultHandle, ResultQuantity))
	{
		return; // 没抽中或奖池为空，直接跳过
	}

	// 第二步：拿着身份证，去查阅 Data Table 里的详细档案
	FTSA_ItemDataRow* RowData = GetItemStaticData(ResultHandle);
	if (!RowData)
	{
		return; // 表里查无此物
	}

	// 第三步：将 Handle、数量 和 查到的分类Tag 交给工厂，生成对应的动态数据外壳
	FInstancedStruct ManifestStruct = CreateManifestByTag(ResultHandle, ResultQuantity, RowData->Category);

	// 第四步：安全地塞入背包组件
	if (ManifestStruct.IsValid())
	{
		InventoryComponent->TryAddItem(ManifestStruct);
	}
}

FTSA_ItemDataRow* ATSA_Container::GetItemStaticData(const FDataTableRowHandle& Handle) const
{
	// 防止空指针崩溃
	if (Handle.DataTable == nullptr || Handle.RowName.IsNone())
	{
		return nullptr;
	}

	FString ContextString(TEXT("Container Spawn Item Lookup"));
	return Handle.DataTable->FindRow<FTSA_ItemDataRow>(Handle.RowName, ContextString);
}

FInstancedStruct ATSA_Container::CreateManifestByTag(const FDataTableRowHandle& Handle, int32 Quantity,const FGameplayTag& CategoryTag) const
{
	
	FTSA_ItemManifest Manifest;
	Manifest.ItemDataHandle = Handle;
	Manifest.StackCount = Quantity;
	
	FString ContextString(TEXT("Container Spawn Item Manifest"));
	UTSA_ItemUtils::MakeManifestFromItemDataRow(Manifest, *Handle.GetRow<FTSA_ItemDataRow>(ContextString));
	return FInstancedStruct::Make(Manifest);
	
}

