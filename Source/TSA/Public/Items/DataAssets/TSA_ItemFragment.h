// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "TSA_ItemFragment.generated.h"

class UGameplayAbility;
class UGameplayEffect;
/**
 * 
 */
UCLASS(DefaultToInstanced, EditInlineNew, Abstract)
class TSA_API UTSA_ItemFragment : public UObject
{
	GENERATED_BODY()
};

UCLASS()
class TSA_API UTSA_AttributeFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TSubclassOf<UGameplayEffect> AttributeGEClass;
};

UCLASS()
class TSA_API UTSA_AbilityFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Attributes")
	TArray<TSubclassOf<UGameplayAbility>> AbilityClasses;
};

UCLASS()
class TSA_API UTSA_WeaponFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	
};

UCLASS()
class TSA_API UTSA_ArmorFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	
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
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Props")
	bool bDisposable = false;
};

UCLASS()
class TSA_API UTSA_EnergyFragment : public UTSA_ItemFragment
{
	GENERATED_BODY()
public:
	
};