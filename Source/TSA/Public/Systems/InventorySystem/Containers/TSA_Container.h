// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/Actor.h"
#include "Interaction/TSA_InteractableActor.h"
#include "StructUtils/InstancedStruct.h"
#include "TSA_Container.generated.h"

struct FTSA_ItemDataRow;
class UTSA_RandomItemPool;
class UTSA_InventoryComponent;

UCLASS()
class TSA_API ATSA_Container : public ATSA_InteractableActor
{
	GENERATED_BODY()

public:
	ATSA_Container();
	
	virtual void PrimaryInteract_Implementation(APlayerController* Interactor) override;

protected:
	virtual void BeginPlay() override;
	virtual void GetLifetimeReplicatedProps(TArray<class FLifetimeProperty>& OutLifetimeProps) const override;
	
	UFUNCTION(BlueprintCallable, Server, Reliable)
	virtual void Server_SpawnItems();
	
private:
	
	// 负责执行单次物品生成的完整流水线
	void GenerateSingleItem(UTSA_RandomItemPool* LoadedPool);

	// 辅助函数：根据 Handle 去 Data Table 中查出静态数据
	FTSA_ItemDataRow* GetItemStaticData(const FDataTableRowHandle& Handle) const;

	// 核心工厂函数：根据标签，自动打包出正确的 FInstancedStruct
	FInstancedStruct CreateManifestByTag(const FDataTableRowHandle& Handle, int32 Quantity, const FGameplayTag& CategoryTag) const;
	
	/* Inventory Component */
	UPROPERTY(EditAnywhere,Category="TSA|Inventory")
	FText ContainerName;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory")
	TSoftObjectPtr<UTSA_RandomItemPool> ItemPool;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory")
	int32 MinItemCount = 2;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory")
	int32 MaxItemCount = 4;
	
	UPROPERTY(VisibleAnywhere, Replicated, Category = "TSA|Inventory")
	TObjectPtr<UTSA_InventoryComponent> InventoryComponent;
	
	bool bIsSpawned = false;
	/* End of Inventory Component */
};
