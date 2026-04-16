// Dark Trace Studio Works


#include "Game/GISubsystem/TSA_StaticDataSubsystem.h"

#include "AbilitySystem/AttributeSets/TSA_CombatAttributeSet.h"
#include "AbilitySystem/AttributeSets/TSA_CoreAttributeSet.h"
#include "AbilitySystem/AttributeSets/TSA_ResourceAttributeSet.h"
#include "AbilitySystem/AttributeSets/TSA_VitalAttributeSet.h"
#include "AbilitySystem/DataTable/TSA_AttributeDataRow.h"
#include "TSA/TSA.h"

bool UTSA_StaticDataSubsystem::InitAttributeInfo()
{
	if (!AttributeDataTable.IsNull())
	{
		UDataTable* AttributeInfo = AttributeDataTable.LoadSynchronous();
		if (!AttributeInfo) return true;
		for (auto& Row : AttributeInfo->GetRowMap())
		{
			FTSA_AttributeDataRow* AttributeDataRow = reinterpret_cast<FTSA_AttributeDataRow*>(Row.Value);
			AttributeDataRows.Add(AttributeDataRow->AttributeTag, *AttributeDataRow);
		}
	}
	return false;
}

void UTSA_StaticDataSubsystem::Initialize(FSubsystemCollectionBase& Collection)
{
	Super::Initialize(Collection);
	
	if (!InitAttributeInfo())
	{
		UE_LOG(LogTSA, Error, TEXT("Failed to initialize attribute info"));
	}
	SetAttributeStrings();
}

void UTSA_StaticDataSubsystem::SetAttributeStrings()
{
	AttributeStrings.Reserve(40);
	// Vital Set
	AttributeStrings.Add(UTSA_VitalAttributeSet::GetHealthAttribute(),FString("<Health>"+FString(TEXT("生命值"))+"</>"));
	AttributeStrings.Add(UTSA_VitalAttributeSet::GetMaxHealthAttribute(),FString("<Health>"+FString(TEXT("最大生命值"))+"</>"));
	AttributeStrings.Add(UTSA_VitalAttributeSet::GetHealthConsumeRateAttribute(),FString("<Health>"+FString(TEXT("生命值消耗/s"))+"</>"));
	AttributeStrings.Add(UTSA_VitalAttributeSet::GetHealthRegenRateAttribute(),"<Health>"+FString(TEXT("生命值回复/s"))+"</>");
	AttributeStrings.Add(UTSA_VitalAttributeSet::GetArmorAttribute(),"<Armor>"+FString(TEXT("护甲值"))+"</>");
	AttributeStrings.Add(UTSA_VitalAttributeSet::GetMaxArmorAttribute(),"<Armor>"+FString(TEXT("最大护甲值"))+"</>");
	AttributeStrings.Add(UTSA_VitalAttributeSet::GetArmorConsumeRateAttribute(),"<Armor>"+FString(TEXT("护甲值消耗/s"))+"</>");
	AttributeStrings.Add(UTSA_VitalAttributeSet::GetArmorRegenRateAttribute(),"<Armor>"+FString(TEXT("护甲值回复/s"))+"</>");
	// Core Set
	AttributeStrings.Add(UTSA_CoreAttributeSet::GetMasteryAttribute(),"<Core>"+FString(TEXT("掌控"))+"</>");
	AttributeStrings.Add(UTSA_CoreAttributeSet::GetReactionAttribute(),"<Core>"+FString(TEXT("反应"))+"</>");
	AttributeStrings.Add(UTSA_CoreAttributeSet::GetCalculationAttribute(),"<Core>"+FString(TEXT("计算"))+"</>");
	AttributeStrings.Add(UTSA_CoreAttributeSet::GetObservationAttribute(),"<Core>"+FString(TEXT("观察"))+"</>");
	AttributeStrings.Add(UTSA_CoreAttributeSet::GetTenacityAttribute(),"<Core>"+FString(TEXT("坚韧"))+"</>");
	AttributeStrings.Add(UTSA_CoreAttributeSet::GetResonanceAttribute(),"<Core>"+FString(TEXT("共感"))+"</>");
	// Combat Set
	AttributeStrings.Add(UTSA_CombatAttributeSet::GetCritRateAttribute(),"<Critical>"+FString(TEXT("暴击率"))+"</>");
	AttributeStrings.Add(UTSA_CombatAttributeSet::GetCritDamageAttribute(),"<Critical>"+FString(TEXT("暴击伤害"))+"</>");
	AttributeStrings.Add(UTSA_CombatAttributeSet::GetWeaponCooldownAttribute(),"<Cooldown>"+FString(TEXT("武器冷却"))+"</>");
	AttributeStrings.Add(UTSA_CombatAttributeSet::GetModuleCooldownAttribute(),"<Cooldown>"+FString(TEXT("模块冷却"))+"</>");
	AttributeStrings.Add(UTSA_CombatAttributeSet::GetPropUseSpeedAttribute(),"<Speed>"+FString(TEXT("道具使用速度"))+"</>");
	AttributeStrings.Add(UTSA_CombatAttributeSet::GetMovementSpeedAttribute(),"<Speed>"+FString(TEXT("移动速度"))+"</>");
	AttributeStrings.Add(UTSA_CombatAttributeSet::GetPhysicalResistanceAttribute(),"<Physical>"+FString(TEXT("物理抗性"))+"</>");
	AttributeStrings.Add(UTSA_CombatAttributeSet::GetEnergyResistanceAttribute(),"<Energy>"+FString(TEXT("能量抗性"))+"</>");
	AttributeStrings.Add(UTSA_CombatAttributeSet::GetStructureResistanceAttribute(),"<Structure>"+FString(TEXT("结构抗性"))+"</>");
	// Resource Set
	AttributeStrings.Add(UTSA_ResourceAttributeSet::GetEnergyAttribute(),"<Energy>"+FString(TEXT("能量"))+"</>");
	AttributeStrings.Add(UTSA_ResourceAttributeSet::GetMaxEnergyAttribute(),"<Energy>"+FString(TEXT("最大能量"))+"</>");
	AttributeStrings.Add(UTSA_ResourceAttributeSet::GetEnergyRegenRateAttribute(),"<Energy>"+FString(TEXT("能量回复/s"))+"</>");
	AttributeStrings.Add(UTSA_ResourceAttributeSet::GetEnergyConsumeRateAttribute(),"<Energy>"+FString(TEXT("能量消耗/s"))+"</>");
	AttributeStrings.Add(UTSA_ResourceAttributeSet::GetMatterAttribute(),"<Physical>"+FString(TEXT("物质量"))+"</>");
	AttributeStrings.Add(UTSA_ResourceAttributeSet::GetMaxMatterAttribute(),"<Physical>"+FString(TEXT("最大物质量"))+"</>");
	AttributeStrings.Add(UTSA_ResourceAttributeSet::GetMatterRegenRateAttribute(),"<Physical>"+FString(TEXT("物质量回复/s"))+"</>");
	AttributeStrings.Add(UTSA_ResourceAttributeSet::GetMatterConsumeRateAttribute(),"<Physical>"+FString(TEXT("物质量消耗/s"))+"</>");
	AttributeStrings.Add(UTSA_ResourceAttributeSet::GetConversionRateAttribute(),"<Core>"+FString(TEXT("转换率"))+"</>");
	AttributeStrings.Add(UTSA_ResourceAttributeSet::GetPrintSpeedAttribute(),"<Speed>"+FString(TEXT("打印速度"))+"</>");
	AttributeStrings.Add(UTSA_ResourceAttributeSet::GetSearchSpeedAttribute(),"<Speed>"+FString(TEXT("搜索速度"))+"</>");
}

const FTSA_AttributeDataRow* UTSA_StaticDataSubsystem::FindAttributeDataRow(const FGameplayTag& AttributeTag)
{
	return AttributeDataRows.Find(AttributeTag);
}
