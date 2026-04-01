#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h" 

namespace AbilityTags
{
	namespace Converter
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(ConvertItem);
		

	}

	namespace SetByCaller
	{
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(Duration);
		UE_DECLARE_GAMEPLAY_TAG_EXTERN(YieldPerSec);
	}
}
