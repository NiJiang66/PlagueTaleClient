// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Scripts/PtEventData.h"
#include "PtChatRoom.generated.h"


class USizeBox;
class UScrollBox;
class UEditableText;
class UPtChatItem;
class UImage;

/**
 *	聊天界面
 */
UCLASS()
class PLAGUETALE_API UPtChatRoom : public UUserWidget
{
	GENERATED_BODY()

public:

	/**	由UPtMainGameWidget触发注册事件 */
	void InstallEvent();

	/**	注销事件 */
	void UnInstallEvents();

	/**	发送聊天消息 */
	UFUNCTION(BlueprintCallable)
	void SendChatInfo();

	/**	接受聊天消息 */
	void OnAcceptChatList(const UKBEventData* EventData);

	/**	显示隐藏输入框 */
	UFUNCTION(BlueprintCallable)
	void ShowOrHideInput(bool IsShow, bool IsWrite = false);

public:

	UPROPERTY(Meta = (BindWidget))
	USizeBox* ChatInputBox;

	UPROPERTY(Meta = (BindWidget))
	UScrollBox* ChatScrollBox;

	UPROPERTY(Meta = (BindWidget))
	UImage* BgImg;

	UPROPERTY(Meta = (BindWidget))
	UEditableText* InputTextBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UPtChatItem> ChatItemClass;

	/**	重新计时隐藏聊天栏时间 */
	UPROPERTY(BlueprintReadWrite)
	bool ResetCounting = true;
	/**	是否在输入中 */
	UPROPERTY(BlueprintReadOnly)
	bool IsWriting = false;
};
