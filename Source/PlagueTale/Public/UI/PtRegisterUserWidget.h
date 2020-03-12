// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"

#include "PtRegisterUserWidget.generated.h"

class UButton;
class UEditableTextBox;
class UCircularThrobber;
class APtStartGameMode;
class UPtMessageUserWidget;


/**
 * 游戏注册界面
 */
UCLASS()
class PLAGUETALE_API UPtRegisterUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** 判断控件变量是否加载成功 */
	virtual bool Initialize() override;

	/** 注册按钮点击事件 */
	UFUNCTION()
	void OnRegisterBtnOnClicked();

	/** 账号注册方法，不再使用2020.3.12 */
	void AccountRegisterFromServer(FString&Nickname, FString&Password);
	/** 请求响应方法，不再使用2020.3.12 */
	void RequestComplete(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess);

public:

	/** 创建回退按钮变量 */
	UPROPERTY()
	UButton* BackBtn;

	/** 创建注册账号按钮变量 */
	UPROPERTY()
	UButton* RegisterBtn;

	/** 创建昵称输入框变量 */
	UPROPERTY()
	UEditableTextBox* NicknameInput;

	/** 创建密码输入框变量 */
	UPROPERTY()
	UEditableTextBox * PasswordInput;

	/** 创建再次输入密码输入框变量 */
	UPROPERTY()
	UEditableTextBox* RePasswordInput;

	/** 创建Loading效果 */
	UPROPERTY()
	UCircularThrobber* CircularThrobber;

	/* 初始化Message框*/
	UPROPERTY()
	UPtMessageUserWidget* MessageUserWidget;

};
