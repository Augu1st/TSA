#include "AbilitySystem/Abilities/TSA_AbilityTags.h"

namespace AbilityTags
{
	namespace Converter
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(ConvertItem,"Ability.Converter.ConvertItem","转换物品");
	}
	
	namespace SetByCaller
	{
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(Duration,"Ability.SetByCaller.Duration","持续时间");
		UE_DEFINE_GAMEPLAY_TAG_COMMENT(YieldPerSec,"Ability.SetByCaller.YieldPerSec","每秒产出");
	}
}