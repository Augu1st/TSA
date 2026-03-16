// Dark Trace Studio Works


#include "Utils/TSA_WidgetUtils.h"

int32 UTSA_WidgetUtils::GetIndexFromPosition(const FIntPoint& Position, const int32 Columns)
{
	return  Position.X + Position.Y * Columns;
}

FIntPoint UTSA_WidgetUtils::GetPositionFromIndex(const int32 Index, const int32 Columns)
{
	return FIntPoint(Index % Columns, Index / Columns);
}
