#pragma once

#include "CoreMinimal.h"

#include "TSA_ItemTypes.generated.h"

UENUM(BlueprintType)
enum class ETSA_ItemRarity : uint8
{
	None		UMETA(DisplayName = "无"),			// R0
	Common      UMETA(DisplayName = "普通 (白)"),	// R1
	Great       UMETA(DisplayName = "优质 (绿)"),	// R2
	Rare        UMETA(DisplayName = "稀有 (蓝)"),	// R3
	Epic        UMETA(DisplayName = "史诗 (紫)"),	// R4
	Legendary   UMETA(DisplayName = "传说 (金)"),	// R5
	Mythic      UMETA(DisplayName = "神话 (红)"),	// R6
	Unique      UMETA(DisplayName = "唯一 (彩)"),	// R7
	Destruction UMETA(DisplayName = "毁灭 (黑)")		// R8
};