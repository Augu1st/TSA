// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Systems/InventorySystem/FastArray/TSA_FastArray.h"
#include "TSA_InventoryComponent.generated.h"

struct FTSA_SlotAvailabilityResult;
class UTSA_ItemComponent;
class UTSA_InventoryBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryItemChange, UTSA_InventoryItem*, Item);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FInventoryMessage, const FText&,  Message);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class TSA_API UTSA_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTSA_InventoryComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "TSA|Inventory")
	bool TryAddItem(UTSA_ItemComponent* ItemComponent);
	
	UFUNCTION(Server, Reliable)
	void Server_AddNewItem(UTSA_ItemComponent* ItemComponent, int32 StackCount);
	
	UFUNCTION(Server, Reliable)
	void Server_AddStacksToItem(UTSA_ItemComponent* ItemComponent, int32 StackCount, int32 Remainder);
	
	void AddRepSubObj(UObject* SubObj);
	
	FTSA_SlotAvailabilityResult HasRoomForItem(UTSA_ItemComponent* ItemComponent);
	UTSA_InventoryItem* GetItemAtIndex(int32 Index) const;
	
	// 供 UI 拖拽时调用 (请求服务器移动物品)
	void RequestMoveItem(int32 FromIndex, int32 ToIndex);
	
	FInventoryItemChange OnItemAdded;
	FInventoryItemChange OnItemRemoved;
	FInventoryMessage NewMessage;
	
	const FGameplayTag& GetAcceptableItemCategory() const { return InventoryCategory; }
	
	int32 GetRows() const { return Rows; }
	int32 GetColumns() const { return Columns; }
	
protected:
	virtual void BeginPlay() override;

	UFUNCTION(Server, Reliable)
	void Server_MoveItem(int32 FromIndex, int32 ToIndex);
	
private:
	bool MatchItemCategory(FGameplayTag& ItemCategory) const;
	
	
	UPROPERTY(Replicated)
	FTSA_InventoryFastArray InventoryList;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory")
	FGameplayTag InventoryCategory = FGameplayTag::EmptyTag;
	
	// 列数
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory")
	int32 Columns = 8;
	
	// 行数
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory")
	int32 Rows = 4;
	
	// 背包最大容量
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory")
	int32 MaxCapacity = 32;
	
	// 当前物品数量
	int32 CurrentItemCount = 0;
};
