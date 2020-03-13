// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PtStartUserWidget.generated.h"

class UButton;
class UTextBlock;

/**
 * 游戏开始界面
 */
UCLASS()
class PLAGUETALE_API UPtStartUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** 重写控件创建完成后初始化方法 */
	virtual bool Initialize() override;

	/** 退出游戏按钮点击事件 */
	UFUNCTION()
	void QuitBtnOnClickedEvent();
	
public:

	/** 开始游戏按钮 */
	UPROPERTY()
	UButton* StartBtn;

	/** 注册账号按钮 */
	UPROPERTY()
	UButton* RegisterBtn;

	/** 退出游戏按钮 */
	UPROPERTY()
	UButton* QuitBtn;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* clientVersionLabel;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* clientScriptVersionLabel;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* serverVerstionLabel;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* serverScriptVersionLabel;

};
