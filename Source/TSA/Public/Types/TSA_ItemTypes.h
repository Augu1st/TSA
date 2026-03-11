#pragma once

#include "CoreMinimal.h"

#include "TSA_ItemTypes.generated.h"

UENUM(BlueprintType)
enum class ETSA_ItemRarity : uint8
{
	General     UMETA(DisplayName = "一般 (灰)"),
	Common      UMETA(DisplayName = "普通 (白)"),
	Great       UMETA(DisplayName = "优质 (绿)"),
	Rare        UMETA(DisplayName = "稀有 (蓝)"),
	Epic        UMETA(DisplayName = "史诗 (紫)"),
	Legendary   UMETA(DisplayName = "传说 (金)"),
	Mythic      UMETA(DisplayName = "神话 (红)"),
	Unique      UMETA(DisplayName = "独特 (彩)"),
	Destruction UMETA(DisplayName = "毁灭 (黑)")
};