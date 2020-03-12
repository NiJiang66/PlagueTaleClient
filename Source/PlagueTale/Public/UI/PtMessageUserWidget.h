// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PtMessageUserWidget.generated.h"

/**
 * 提示框UI
 */
UCLASS()
class PLAGUETALE_API UPtMessageUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	virtual bool Initialize() override;

	/* 设置关闭按钮事件*/
	UFUNCTION()
	void ClosButtonOnClickedEvent();
	
public:

	/* 初始化文本框*/
	UPROPERTY()
	class UTextBlock* MsgBlock;

	/* 初始化关闭按钮*/
	UPROPERTY()
	class UButton* CloseBtn;

};
