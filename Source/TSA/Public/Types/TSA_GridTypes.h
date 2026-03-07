#pragma once

#include "TSA_GridTypes.generated.h"

UENUM()
enum class ETSA_GridType : uint8
{
	General,	// 通用
	Equipment,	// 装备
	Prop,		// 道具
	Collection	// 收集品
};