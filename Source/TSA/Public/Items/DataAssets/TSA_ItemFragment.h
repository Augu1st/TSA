// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AttributeSet.h"
#include "GameplayEffectTypes.h"
#include "UObject/Object.h"
#include "GameplayTagContainer.h"
#include "TSA_ItemFragment.generated.h"

class UGameplayAbility;
class UGameplayEffect;

//单个修饰器
USTRUCT(BlueprintType)
struct FTSA_StatModifier
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FGameplayAttribute Attribute;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TEnumAsByte<EGameplayModOp::Type> ModifierOp = EGameplayModOp::Additive;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float Value = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	TMap<FGameplayAttribute, float> AttributeScales;
};

UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class TSA_API UTSA_ItemFragment : public UObject
{
	GENERATED_BODY()
};

// 装备属性片段
UCLASS()
class TSA_API UTSA_EquipStatFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "TSA|Attributes")
	TArray<FTSA_StatModifier> Modifiers;
	
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Attributes")
	FText Description;
};

// 即时效果片段
UCLASS()
class TSA_API UTSA_InstantStatFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "TSA|Attributes")
	TArray<FTSA_StatModifier> Modifiers;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Attributes")
	FText Description;
};

// 持续Buff片段
UCLASS()
class TSA_API UTSA_DurationBuffFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly, Category = "TSA|Attributes")
	TArray<FTSA_StatModifier> Modifiers;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Attributes")
	float Duration = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Attributes")
	FText Description;
};

// 技能片段
UCLASS()
class TSA_API UTSA_AbilityFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Attributes")
	TArray<TSubclassOf<UGameplayAbility>> AbilityClasses;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Attributes")
	FText Description;
};

UCLASS()
class TSA_API UTSA_WeaponFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	
};

// 防具片段
UCLASS()
class TSA_API UTSA_ArmorFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Armor")
	float MaxArmor = 0.f;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Armor")
	FText Description;
};

UCLASS()
class TSA_API UTSA_ModuleFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	
};

UCLASS()
class TSA_API UTSA_PropFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Props")
	bool bDisposable = false;// 是否一次性
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Props")
	float UseTime = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Props")
	FText Description ;
};

UCLASS()
class TSA_API UTSA_EnergyCostFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Energy")
	float MaxEnergy = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Energy")
	FGameplayTag EnergyCostType;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Energy")
	float EnergyCost = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Energy")
	float EnergyCostDuration = 0.f;
};

// 蓝图片段
UCLASS()
class TSA_API UTSA_BlueprintFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Print")
	float MatterCost = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Print")
	float EnergyCost = 0.f;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "TSA|Print")
	float PrintTime = 0.f;
};