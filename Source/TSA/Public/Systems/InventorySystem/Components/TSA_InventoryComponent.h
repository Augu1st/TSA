// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Components/ActorComponent.h"
#include "Systems/InventorySystem/FastArray/TSA_FastArray.h"
#include "TSA_InventoryComponent.generated.h"

class ATSA_ItemActor;
struct FInstancedStruct;
struct FTSA_ItemManifestBase;
struct FTSA_ItemDataRow;
struct FTSA_SlotAvailabilityResult;
class UTSA_ItemComponent;
class UTSA_InventoryBase;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FInventoryItemChange, UTSA_InventoryItem*, Item, int32, SlotIndex);

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent), Blueprintable)
class TSA_API UTSA_InventoryComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UTSA_InventoryComponent();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "TSA|Inventory")
	bool TryAddItem(FInstancedStruct& ItemManifestStruct);
	
	UFUNCTION(BlueprintCallable, Category = "TSA|Inventory")
	void RequestMoveItem(int32 SourceIndex, UTSA_InventoryComponent* TargetComp, int32 TargetIndex);
	
	UFUNCTION(BlueprintCallable, BlueprintAuthorityOnly, Category = "TSA|Inventory")
	void SendItemToPlayer(UTSA_InventoryItem* Item);
	
	UFUNCTION(BlueprintCallable, Category = "TSA|Inventory")
	void RequestDropItemIntoWorld(int32 SlotIndex);
	
	void AddNewItem(FInstancedStruct& ItemManifestStruct, int32 SlotIndex);
	void AddStacksToItem(FInstancedStruct& ItemManifestStruct, int32 AddToStack, int32 SlotIndex);
	void RemoveItem(UTSA_InventoryItem* Item,int32 SlotIndex);
	
	void AddRepSubObj(UObject* SubObj);
	
	FTSA_SlotAvailabilityResult HasRoomForItem(const FInstancedStruct& ItemManifestStruct);
	void TryAddLeftItemToEmptySlot(FTSA_SlotAvailabilityResult& Result, int32 StackToAdd);
	UTSA_InventoryItem* GetItemAtIndex(int32 Index) const;
	TArray<FTSA_ItemSearchResult> GetAllItemEntries();
	const FGameplayTag& GetInventoryCategory() const { return InventoryCategory; }
	bool MatchItemCategory(const FGameplayTag& ItemCategory) const;
	int32 GetRows() const { return Rows; }
	int32 GetColumns() const { return Columns; }
	
	UFUNCTION(Client, Reliable)
	void Client_ShowMessage(const FText& Message);
	
	FInventoryItemChange OnItemAdded;
	FInventoryItemChange OnItemRemoved;
	FInventoryItemChange OnItemChanged;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_MoveItem(int32 SourceIndex, UTSA_InventoryComponent* TargetComp, int32 TargetIndex);
	
	UFUNCTION(Server, Reliable, WithValidation)
	void Server_DropItemIntoWorld(int32 SlotIndex);
	
	UFUNCTION(Client, Reliable)
	void Client_AddItem(UTSA_InventoryItem*  Item, int32 SlotIndex);
	
private:
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
	
	// 当前物品数量(所占槽位)
	int32 CurrentItemCount = 0;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Inventory")
	TSubclassOf<ATSA_ItemActor> ItemActorClass; 
};
