// Dark Trace Studio Works

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "TSA_ResourceAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

UCLASS()
class TSA_API UTSA_ResourceAttributeSet : public UAttributeSet
{
	GENERATED_BODY()
public:
	UTSA_ResourceAttributeSet();
	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
	
	/* Energy 能量 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Energy)
	FGameplayAttributeData Energy;//能量
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, Energy)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxEnergy)
	FGameplayAttributeData MaxEnergy;//最大能量
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, MaxEnergy)
	
	UFUNCTION()
	void OnRep_Energy(const FGameplayAttributeData& OldEnergy);	
	
	UFUNCTION()
	void OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy);
	/* End of Energy */
	
	/* Matter 物质 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Matter)
	FGameplayAttributeData Matter;//物质量
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, Matter)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMatter)
	FGameplayAttributeData MaxMatter;//最大物质量
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, MaxMatter)
	
	UFUNCTION()
	void OnRep_Matter(const FGameplayAttributeData& OldMatter);
			
	UFUNCTION()
	void OnRep_MaxMatter(const FGameplayAttributeData& OldMaxMatter);
	/* End of Matter */
	
	/* Conversion 转换 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ConversionRate)
	FGameplayAttributeData ConversionRate;//转换率
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, ConversionRate)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ConversionSpeed)
	FGameplayAttributeData ConversionSpeed;//转换速度
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, ConversionSpeed)
	
	UFUNCTION()
	void OnRep_ConversionRate(const FGameplayAttributeData& OldConversionRate);
	
	UFUNCTION()
	void OnRep_ConversionSpeed(const FGameplayAttributeData& OldConversionSpeed);
	/* End of ConversionTime */
	
	/* Print 打印 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PrintSpeed)
	FGameplayAttributeData PrintSpeed;//打印速度
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, PrintSpeed)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PrintPower)
	FGameplayAttributeData PrintPower;//打印功率
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, PrintPower)
	
	UFUNCTION()
	void OnRep_PrintSpeed(const FGameplayAttributeData& OldPrintSpeed);
	
	UFUNCTION()
	void OnRep_PrintPower(const FGameplayAttributeData& OldPrintPower);
	/* End of Print */
	
	/* Prop 道具 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PropUseSpeed)
	FGameplayAttributeData PropUseSpeed;//道具使用速度
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, PropUseSpeed)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PropUseEfficiency)
	FGameplayAttributeData PropUseEfficiency;//道具使用效率
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, PropUseEfficiency)
	
	UFUNCTION()
	void OnRep_PropUseSpeed(const FGameplayAttributeData& OldPropUseSpeed);
	
	UFUNCTION()
	void OnRep_PropUseEfficiency(const FGameplayAttributeData& OldPropUseEfficiency);
	/* End of Prop */
	
};
