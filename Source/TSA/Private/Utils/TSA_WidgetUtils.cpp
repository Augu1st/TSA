// Dark Trace Studio Works


#include "Utils/TSA_WidgetUtils.h"

int32 UTSA_WidgetUtils::GetIndexFromPosition(const FIntPoint& Position, const int32 Columns)
{
	return  Position.X + Position.Y * Columns;
}
