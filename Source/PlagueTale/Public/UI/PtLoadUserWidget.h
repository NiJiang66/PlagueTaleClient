// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PtLoadUserWidget.generated.h"

/**
 * 游戏加载界面
 */
UCLASS()
class PLAGUETALE_API UPtLoadUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** 控件创建完成初始化方法 */
	virtual bool Initialize() override;

	/** 重写Tick */
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime)override;

	/** 设置开始加载 */
	void SetStartLoad();

	/** 结束加载 */
	void SetEndLoad();
	
public:

	/** 加载进度条 */
	UPROPERTY()
	class UCircularThrobber* CircularThrobber;

	/** 加载文本 */
	UPROPERTY()
	class UTextBlock* LoadingText;

	/** 继续按钮 */
	UPROPERTY()
	class UButton* NextButton;

private:

	/** 保存游戏实例 */
	class UPTGameInstance* PtGameInstance = nullptr;

};
