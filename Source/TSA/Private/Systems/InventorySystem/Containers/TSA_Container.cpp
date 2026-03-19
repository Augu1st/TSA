// Dark Trace Studio Works


#include "Systems/InventorySystem/Containers/TSA_Container.h"

#include "Items/Manifest/TSA_ItemManifest.h"
#include "Systems/InventorySystem/Components/TSA_InventoryComponent.h"
#include "Systems/InventorySystem/Containers/TSA_RandomItemPool.h"
#include "TSA/TSA.h"
#include "TSA_GameplayTags.h"
#include "Player/TSA_PlayerController.h"


ATSA_Container::ATSA_Container()
{
	PrimaryActorTick.bCanEverTick = false;
	
	InventoryComponent = CreateDefaultSubobject<UTSA_InventoryComponent>(TEXT("InventoryComponent"));
}

void ATSA_Container::PrimaryInteract_Implementation(APlayerController* Interactor)
{
	ATSA_PlayerController* PlayerController = Cast<ATSA_PlayerController>(Interactor);
	if (!IsValid(PlayerController)) return;
	if (!bIsSpawned)
	{
		SpawnItems();
		bIsSpawned = true;
	}
	PlayerController->OpenContainerInventory(InventoryComponent);
}

void ATSA_Container::BeginPlay()
{
	Super::BeginPlay();
	
}

void ATSA_Container::SpawnItems()
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
		return; // 表里查无此物（可能策划配错表了）
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
	// 情况A：是装备 (包括 Weapon, Armor 等所有子标签)
	if (CategoryTag.MatchesTag(ItemTags::Category::Equipment))
	{
		FTSA_EquipmentManifest EquipManifest;
		EquipManifest.ItemDataHandle = Handle;
		EquipManifest.StackCount = Quantity;
		
		return FInstancedStruct::Make(EquipManifest);
	}
    
	// 情况B：是道具
	if (CategoryTag.MatchesTag(ItemTags::Category::Prop))
	{
		FTSA_PropManifest PropManifest;
		PropManifest.ItemDataHandle = Handle;
		PropManifest.StackCount = Quantity;
        
		return FInstancedStruct::Make(PropManifest);
	}
    
	// 情况C：是收集品
	if (CategoryTag.MatchesTag(ItemTags::Category::Collection))
	{
		FTSA_CollectionManifest CollectionManifest;
		CollectionManifest.ItemDataHandle = Handle;
		CollectionManifest.StackCount = Quantity;
		// 可以在这里扩展鉴定状态等：
		// CollectionManifest.bIsIdentified = false;
        
		return FInstancedStruct::Make(CollectionManifest);
	}
    
	// 情况D：通用保底处理 (如果 Tag 没配，或者配的是 General)
	
	FTSA_ItemManifestBase BaseManifest;
	BaseManifest.ItemDataHandle = Handle;
	BaseManifest.StackCount = Quantity;
        
	return FInstancedStruct::Make(BaseManifest);
	
}

