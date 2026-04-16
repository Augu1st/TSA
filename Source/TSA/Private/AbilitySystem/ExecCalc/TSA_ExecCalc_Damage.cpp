// Dark Trace Studio Works


#include "AbilitySystem/ExecCalc/TSA_ExecCalc_Damage.h"

#include "TSA_GameplayTags.h"
#include "AbilitySystem/AttributeSets/TSA_CombatAttributeSet.h"
#include "AbilitySystem/AttributeSets/TSA_CoreAttributeSet.h"
#include "AbilitySystem/AttributeSets/TSA_VitalAttributeSet.h"


struct FDamageStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritRate);// 暴击率
	DECLARE_ATTRIBUTE_CAPTUREDEF(CritDamage);// 暴击伤害
	
	DECLARE_ATTRIBUTE_CAPTUREDEF(PhysicalResistance);// 物理抗性
	DECLARE_ATTRIBUTE_CAPTUREDEF(EnergyResistance);// 能量抗性
	DECLARE_ATTRIBUTE_CAPTUREDEF(StructureResistance);// 结构抗性
	
	FDamageStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTSA_CombatAttributeSet,CritRate,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTSA_CombatAttributeSet,CritDamage,Source,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTSA_CombatAttributeSet,PhysicalResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTSA_CombatAttributeSet,EnergyResistance,Target,false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UTSA_CombatAttributeSet,StructureResistance,Target,false);
	}
};

static const FDamageStatics& DamageStatics()
{
	static FDamageStatics DStatics;
	return DStatics;
}

UTSA_ExecCalc_Damage::UTSA_ExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(DamageStatics().CritRateDef);
	RelevantAttributesToCapture.Add(DamageStatics().CritDamageDef);
	RelevantAttributesToCapture.Add(DamageStatics().PhysicalResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().EnergyResistanceDef);
	RelevantAttributesToCapture.Add(DamageStatics().StructureResistanceDef);
}

void UTSA_ExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	FAggregatorEvaluateParameters EvaluationParameters;
	EvaluationParameters.SourceTags = &ExecutionParams.GetPassedInTags();
	EvaluationParameters.TargetTags = &ExecutionParams.GetPassedInTags();
	// 暴击
	float CritRate = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().CritRateDef,EvaluationParameters,CritRate);
		CritRate = FMath::Clamp(CritRate,0.f,1.f);
	float CritDamage = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().CritDamageDef,EvaluationParameters,CritDamage);
	
	// 物理
	float PhysicalBaseDamage = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(
		CombatTags::Damage::PhysicalDamage,false,0.f);
	float ImpactValue = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(
		CombatTags::Damage::Impact,false,0.f);
	float CuttingValue = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(
		CombatTags::Damage::Cutting,false,0.f);
	// 能量
	float EnergyBaseDamage = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(
		CombatTags::Damage::EnergyDamage,false,0.f);
	float ElectricityValue = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(
		CombatTags::Damage::Electricity,false,0.f);
	float HeatValue = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(
		CombatTags::Damage::Heat,false,0.f);
	// 结构
	float StructureBaseDamage = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(
		CombatTags::Damage::StructureDamage,false,0.f);
	float ParticleValue = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(
		CombatTags::Damage::Particle,false,0.f);
	float DecomposeValue = ExecutionParams.GetOwningSpec().GetSetByCallerMagnitude(
		CombatTags::Damage::Decompose,false,0.f);
	// 抗性
	float PhysicalResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().PhysicalResistanceDef,EvaluationParameters,PhysicalResistance);
	PhysicalResistance = FMath::Max(PhysicalResistance,0.f);
	float EnergyResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().EnergyResistanceDef,EvaluationParameters,EnergyResistance);
	EnergyResistance = FMath::Max(EnergyResistance,0.f);
	float StructureResistance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(
		DamageStatics().StructureResistanceDef,EvaluationParameters,StructureResistance);
	StructureResistance = FMath::Max(StructureResistance,0.f);
	
	float FinalDamage = 0.f;
	float HealthDamage = 0.f;
	// 1. 计算暴击伤害
	if (CritRate > 0.f && FMath::FRand() <= CritRate)
	{
		PhysicalBaseDamage *= CritDamage;
		EnergyBaseDamage *= CritDamage;
		StructureBaseDamage *= CritDamage;
	}	
	// 2. 分解 降低所有抗性
	if(DecomposeValue > 0.f)
	{
		float LeftPercent = 1.f - DecomposeValue/(DecomposeValue + 100);
		PhysicalResistance *= LeftPercent;
		EnergyResistance *= LeftPercent;
		StructureResistance *= LeftPercent;
	}
	// 3. 计算减免后伤害/Debuff
	if (PhysicalBaseDamage>0.f && PhysicalResistance>0.f)
	{
		float DecreaseRate = PhysicalResistance/(PhysicalResistance + 200);
		PhysicalBaseDamage *= 1.f - DecreaseRate;
		ImpactValue *= 1.f - DecreaseRate;
		CuttingValue *= 1.f - DecreaseRate;
	}
	if (EnergyBaseDamage>0.f && EnergyResistance>0.f)
	{
		float DecreaseRate = EnergyResistance/(EnergyResistance + 200);
		EnergyBaseDamage *= 1.f - DecreaseRate;
		ElectricityValue *= 1.f - DecreaseRate;
		HeatValue *= 1.f - DecreaseRate;
	}
	if (StructureBaseDamage>0.f && StructureResistance>0.f)
	{
		StructureBaseDamage *= 1.f - StructureResistance/(StructureResistance + 200);
	}
	// 4. 计算最终伤害和生命值伤害
	FinalDamage = PhysicalBaseDamage + EnergyBaseDamage;
	if (ParticleValue > 0.f)
	{
		// 粒子直接造成生命值伤害
		HealthDamage = StructureBaseDamage;
	}
	else FinalDamage += StructureBaseDamage;
	
	OutExecutionOutput.AddOutputModifier(
		FGameplayModifierEvaluatedData(UTSA_VitalAttributeSet::GetIncomingDamageAttribute(),
		EGameplayModOp::Additive,FinalDamage));
	if (HealthDamage > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(UTSA_VitalAttributeSet::GetIncomingHealthDamageAttribute(),
			EGameplayModOp::Additive,HealthDamage));
	}
	
	// 6. 添加Debuff
	if (ImpactValue > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(UTSA_CombatAttributeSet::GetStunAttribute(),
			EGameplayModOp::Additive,ImpactValue));
	}
	if (CuttingValue > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(UTSA_CombatAttributeSet::GetBleedAttribute(),
			EGameplayModOp::Additive,CuttingValue));
	}
	if (ElectricityValue > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(UTSA_CombatAttributeSet::GetOverloadAttribute(),
			EGameplayModOp::Additive,ElectricityValue));
	}
	if (HeatValue > 0.f)
	{
		OutExecutionOutput.AddOutputModifier(
			FGameplayModifierEvaluatedData(UTSA_CombatAttributeSet::GetOverheatAttribute(),
			EGameplayModOp::Additive,HeatValue));
	}
}