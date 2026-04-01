// Dark Trace Studio Works


#include "AbilitySystem/Abilities/Converter/TSA_GA_ConvertItem.h"

#include "TSA_GameplayTags.h"
#include "AbilitySystem/Abilities/TSA_AbilityTags.h"
#include "AbilitySystem/AttributeSets/TSA_ResourceAttributeSet.h"
#include "AbilitySystem/Component/TSA_AbilitySystemComponent.h"
#include "Utils/TSA_CommonLibrary.h"

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
	
	// 通知资源管理器将物品数量-1 !!!
	
	FGameplayTag TriggerTag = TriggerEventData->EventTag;
	
	float MatterValue = TriggerEventData->EventMagnitude;
	float ConversionRate = ASC->GetNumericAttribute(UTSA_ResourceAttributeSet::GetConversionRateAttribute());
	
	float ConversionDuration = 1.0f;
	if (MatterValue > 4.0)ConversionDuration = FMath::Sqrt(MatterValue);
	
	float ActualYieldPerSec = 0;
	
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
			SpecHandle.Data.Get()->SetSetByCallerMagnitude(
				AbilityTags::SetByCaller::Duration, ConversionDuration);
			SpecHandle.Data.Get()->SetSetByCallerMagnitude(
				AbilityTags::SetByCaller::YieldPerSec, ActualYieldPerSec);

			ASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
		}
	}
	
	EndAbility(Handle, ActorInfo, ActivationInfo, false, false);
}
