// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "GameplayTagContainer.h"
#include "AbilitySystem/DataTable/TSA_AttributeDataRow.h"
#include "TSA_GameInstanceSys.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class TSA_API UTSA_GameInstanceSys : public UGameInstanceSubsystem
{
	GENERATED_BODY()
	
public:
	bool InitAttributeInfo();
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	
	void SetAttributeStrings();
	
	const FTSA_AttributeDataRow* FindAttributeDataRow(const FGameplayTag& AttributeTag);
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "TSA|Attribute")
	TSoftObjectPtr<UDataTable> AttributeDataTable;
	
	UPROPERTY()
	TMap<FGameplayTag,FTSA_AttributeDataRow> AttributeDataRows;
	
	UPROPERTY(EditAnywhere, Category = "TSA|Item Details")
	TMap<FGameplayAttribute,FString> AttributeStrings;
	
};
