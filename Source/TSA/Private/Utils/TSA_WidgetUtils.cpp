// Dark Trace Studio Works


#include "Utils/TSA_WidgetUtils.h"

#include "Blueprint/SlateBlueprintLibrary.h"

FVector2D UTSA_WidgetUtils::GetViewportPositionFromMouseEvent(UObject* WorldContextObject,
                                                              const FPointerEvent& MouseEvent)
{
	// 安全校验，防止传入空指针导致崩溃
	if (!WorldContextObject)
	{
		return FVector2D::ZeroVector;
	}

	// 1. 获取屏幕绝对坐标
	FVector2D AbsoluteMousePos = MouseEvent.GetScreenSpacePosition();

	// 2. 转换为视口坐标
	FVector2D PixelPosition;
	FVector2D ViewportPosition;
	USlateBlueprintLibrary::AbsoluteToViewport(WorldContextObject, AbsoluteMousePos, PixelPosition, ViewportPosition);

	// 3. 返回完美匹配屏幕的视口坐标
	return ViewportPosition;
}

int32 UTSA_WidgetUtils::GetIndexFromPosition(const FIntPoint& Position, const int32 Columns)
{
	return  Position.X + Position.Y * Columns ;
}

FIntPoint UTSA_WidgetUtils::GetPositionFromIndex(const int32 Index, const int32 Columns)
{
	return FIntPoint(Index % Columns, Index / Columns);
}
