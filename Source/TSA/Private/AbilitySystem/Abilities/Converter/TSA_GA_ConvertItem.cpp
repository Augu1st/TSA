// Dark Trace Studio Works


#include "AbilitySystem/Abilities/Converter/TSA_GA_ConvertItem.h"

#include "TSA_GameplayTags.h"
#include "AbilitySystem/Abilities/TSA_AbilityTags.h"
#include "AbilitySystem/AttributeSets/TSA_ResourceAttributeSet.h"
#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"
#include "Characters/PlayerCharacters/TSA_AgentCharacter.h"
#include "Utils/TSA_CommonLibrary.h"
#include "Abilities/Tasks/AbilityTask_WaitGameplayEffectRemoved.h"

void UTSA_GA_ConvertItem::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                          const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                          const FGameplayEventData* TriggerEventData)
{
	UTSA_AbilitySystemComponent* ASC = Cast<UTSA_AbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());
	if (!CommitAbility(Handle, ActorInfo, ActivationInfo) || !TriggerEventData || !ASC)
	{
		EndAbility(Handle, ActorInfo, ActivationInfo, true, true);
		return;
	}
	
	FGameplayTag TriggerTag = TriggerEventData->EventTag;
	
	float MatterValue = TriggerEventData->EventMagnitude;
	float ConversionRate = ASC->GetNumericAttribute(UTSA_ResourceAttributeSet::GetConversionRateAttribute());
	
	// 计算转换时间
	float ConversionDuration = 1.0f;
	if (MatterValue > 4.0)ConversionDuration = FMath::Sqrt(MatterValue);
	
	float ActualYieldPerSec = 0;
	
	// 选择转换效果，计算每秒产出
	TSubclassOf<UGameplayEffect> ConversionEffect = nullptr;
	if (TriggerTag.MatchesTagExact(EventTags::Converter::ItemToMatter))
	{
		ActualYieldPerSec = (MatterValue*ConversionRate) / ConversionDuration;
		ConversionEffect = ProduceMatter;
	}
	else if (TriggerTag.MatchesTagExact(EventTags::Converter::ItemToEnergy))
	{
		float EnergyValue = MatterValue * UTSA_CommonLibrary::GetConversionRatio(GetWorld());
		ActualYieldPerSec = (EnergyValue*ConversionRate) / ConversionDuration;
		ConversionEffect = ProduceEnergy;
	}
	
	if (ConversionEffect)
	{
		FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
		ContextHandle.AddInstigator(ActorInfo->AvatarActor.Get(), ActorInfo->AvatarActor.Get());
        
		FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(ConversionEffect, 1.0f, ContextHandle);

		if (SpecHandle.IsValid())
		{
			// 注入持续时间和每秒产量
			SpecHandle.Data.Get()->SetSetByCallerMagnitude(AbilityTags::SetByCaller::Duration, ConversionDuration);
			SpecHandle.Data.Get()->SetSetByCallerMagnitude(AbilityTags::SetByCaller::YieldPerSec, ActualYieldPerSec);
			
			//保存应用后的 GE 句柄
			ConversionGEHandle = ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
			
			//开启任务，挂起 GA，等待这个 GE 消失
			UAbilityTask_WaitGameplayEffectRemoved* WaitTask = UAbilityTask_WaitGameplayEffectRemoved::WaitForGameplayEffectRemoved(this, ConversionGEHandle);
			WaitTask->OnRemoved.AddDynamic(this, &UTSA_GA_ConvertItem::OnConversionEffectRemoved);
			WaitTask->ReadyForActivation();
		}
	}
}

void UTSA_GA_ConvertItem::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	UTSA_AbilitySystemComponent* ASC = Cast<UTSA_AbilitySystemComponent>(ActorInfo->AbilitySystemComponent.Get());
	
	// 如果被取消，手动清理转换GE
	if (bWasCancelled && ASC && ConversionGEHandle.IsValid())
	{
		ASC->RemoveActiveGameplayEffect(ConversionGEHandle);
	}
	
	// 不管是否完成转换，都要消耗物品
	ATSA_AgentCharacter* Agent = Cast<ATSA_AgentCharacter>(GetAvatarActorFromActorInfo());
	if (Agent)
	{
		Agent->ConsumeItemInConverter();
	}
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UTSA_GA_ConvertItem::OnConversionEffectRemoved(const FGameplayEffectRemovalInfo& InGameplayEffectRemovalInfo)
{
	EndAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true, false);
}
