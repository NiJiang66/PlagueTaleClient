// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PtChatItem.generated.h"


class UTextBlock;

/**
 * 聊天条目
 */
UCLASS()
class PLAGUETALE_API UPtChatItem : public UUserWidget
{
	GENERATED_BODY()

public:

	/**	初始化数据 */
	void InitItem(FString Name, FString Date, FString Message);

	/**	在蓝图中实现的逐渐隐藏然后销毁的函数 */
	UFUNCTION(BlueprintImplementableEvent)
	void DisappearProcess();

public:

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* UserText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* InfoText;
	
};
