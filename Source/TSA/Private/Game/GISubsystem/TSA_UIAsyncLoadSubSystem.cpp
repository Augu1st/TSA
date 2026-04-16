// Dark Trace Studio Works


#include "Game/GISubsystem/TSA_UIAsyncLoadSubSystem.h"

#include "Components/Image.h"
#include "Engine/AssetManager.h"
#include "Engine/StreamableManager.h"

void UTSA_UIAsyncLoadSubSystem::RequestAsyncLoadImage(UImage* TargetImage, TSoftObjectPtr<UTexture2D> SoftTexture)
{
	if (!TargetImage) return;
	CleanupInvalidTasks();

	TWeakObjectPtr<UImage> WeakImage(TargetImage);

	// 1. 处理竞态条件（ListView防错）：检查这个Image是否正在加载其他图片
	if (TSharedPtr<FStreamableHandle>* ExistingHandle = ActiveLoadTasks.Find(WeakImage))
	{
		if (ExistingHandle->IsValid() && (*ExistingHandle)->IsActive())
		{
			// 取消旧的加载任务！
			(*ExistingHandle)->CancelHandle();
		}
		ActiveLoadTasks.Remove(WeakImage);
	}

	// 2. 如果传入的是空图，直接清空显示并返回
	if (SoftTexture.IsNull())
	{
		TargetImage->SetBrushFromTexture(nullptr);
		return;
	}

	// 3. 如果已经在内存中了，直接同步加载，不走异步开销
	if (SoftTexture.IsValid())
	{
		TargetImage->SetBrushFromTexture(SoftTexture.Get());
		return;
	}

	// 4. 发起异步加载
	FStreamableManager& StreamableManager = UAssetManager::GetStreamableManager();
	
	TSharedPtr<FStreamableHandle> NewHandle = StreamableManager.RequestAsyncLoad(
		SoftTexture.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this, WeakImage, SoftTexture]()
		{
			if (WeakImage.IsValid())
			{
				UTexture2D* LoadedTexture = SoftTexture.Get();
				if (LoadedTexture)
				{
					WeakImage->SetBrushFromTexture(LoadedTexture);
				}
				ActiveLoadTasks.Remove(WeakImage);
			}
		})
	);

	// 5. 将新任务记录到管家中
	if (NewHandle.IsValid() && NewHandle->IsActive())
	{
		ActiveLoadTasks.Add(WeakImage, NewHandle);
	}
}

void UTSA_UIAsyncLoadSubSystem::CleanupInvalidTasks()
{
	for (auto It = ActiveLoadTasks.CreateIterator(); It; ++It)
	{
		if (!It.Key().IsValid())
		{
			if (It.Value().IsValid() && It.Value()->IsActive())
			{
				It.Value()->CancelHandle();
			}
			It.RemoveCurrent();
		}
	}
}
