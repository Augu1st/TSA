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
	
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostAttributeChange(const FGameplayAttribute& Attribute, float OldValue, float NewValue) override;
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;
	
	/* Energy 能量 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Energy)
	FGameplayAttributeData Energy;//能量
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, Energy)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxEnergy)
	FGameplayAttributeData MaxEnergy;//最大能量
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, MaxEnergy)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_EnergyRegenRate)
	FGameplayAttributeData EnergyRegenRate;//能量回复率
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, EnergyRegenRate)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_EnergyConsumeRate)
	FGameplayAttributeData EnergyConsumeRate;//能量消耗率
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, EnergyConsumeRate)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_EnergyNetFlow)
	FGameplayAttributeData EnergyNetFlow;//能量变化率
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, EnergyNetFlow)
	
	UFUNCTION()
	void OnRep_Energy(const FGameplayAttributeData& OldEnergy);	
	
	UFUNCTION()
	void OnRep_MaxEnergy(const FGameplayAttributeData& OldMaxEnergy);
	
	UFUNCTION()
	void OnRep_EnergyRegenRate(const FGameplayAttributeData& OldEnergyRegenRate);
	
	UFUNCTION()
	void OnRep_EnergyConsumeRate(const FGameplayAttributeData& OldEnergyConsumeRate);
	
	UFUNCTION()
	void OnRep_EnergyNetFlow(const FGameplayAttributeData& OldEnergyNetFlow);
	/* End of Energy */
	
	/* Matter 物质 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_Matter)
	FGameplayAttributeData Matter;//物质量
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, Matter)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MaxMatter)
	FGameplayAttributeData MaxMatter;//最大物质量
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, MaxMatter)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MatterRegenRate)
	FGameplayAttributeData MatterRegenRate;// 物质回复率
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, MatterRegenRate)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MatterConsumeRate)
	FGameplayAttributeData MatterConsumeRate;//物质消耗率
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, MatterConsumeRate)
	
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_MatterNetFlow)
	FGameplayAttributeData MatterNetFlow;//物质变化率
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, MatterNetFlow)
	
	UFUNCTION()
	void OnRep_Matter(const FGameplayAttributeData& OldMatter);
			
	UFUNCTION()
	void OnRep_MaxMatter(const FGameplayAttributeData& OldMaxMatter);
	
	UFUNCTION()
	void OnRep_MatterRegenRate(const FGameplayAttributeData& OldMatterRegenRate);
	
	UFUNCTION()
	void OnRep_MatterConsumeRate(const FGameplayAttributeData& OldMatterConsumeRate);
	
	UFUNCTION()
	void OnRep_MatterNetFlow(const FGameplayAttributeData& OldMatterNetFlow);
	/* End of Matter */
	
	/* Conversion 转换 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_ConversionRate)
	FGameplayAttributeData ConversionRate;//转换率
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, ConversionRate)
	
	UFUNCTION()
	void OnRep_ConversionRate(const FGameplayAttributeData& OldConversionRate);
	/* End of ConversionTime */
	
	/* Print 打印 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_PrintSpeed)
	FGameplayAttributeData PrintSpeed;//打印速度
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, PrintSpeed)
	
	UFUNCTION()
	void OnRep_PrintSpeed(const FGameplayAttributeData& OldPrintSpeed);
	/* End of Print */
	
	/* Search 搜索 */
	UPROPERTY(BlueprintReadOnly, ReplicatedUsing=OnRep_SearchSpeed)
	FGameplayAttributeData SearchSpeed;//搜索速度
	ATTRIBUTE_ACCESSORS(UTSA_ResourceAttributeSet, SearchSpeed)
	
	UFUNCTION()
	void OnRep_SearchSpeed(const FGameplayAttributeData& OldSearchSpeed);
	/* End of Search */
};
