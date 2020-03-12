// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"

#include "Runtime/Online/HTTP/Public/HttpModule.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpRequest.h"
#include "Runtime/Online/HTTP/Public/Interfaces/IHttpResponse.h"

#include "PtLoginUserWidget.generated.h"

class UCircularThrobber;
class UButton;
class UEditableTextBox;


/**
 * 游戏登录界面
 */
UCLASS()
class PLAGUETALE_API UPtLoginUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	/** 控件创建完成的初始化方法 */
	virtual bool Initialize() override;

	/** 登录按钮点击事件，不再使用2020.3.12 */
	UFUNCTION()
	void OnLoginBtnOnClicked();

	/** 用户登录的方法，不再使用2020.3.12 */
	void AccountLoginFromServer(FString Nickname, FString Password);
	/** 请求的响应方法，不再使用2020.3.12 */
	void RequestComplete(FHttpRequestPtr RequestPtr, FHttpResponsePtr ResponsePtr, bool bIsSuccess);
	
public:
	/** 返回按钮 */
	UPROPERTY()
	UButton* BackBtn;

	/** 昵称输入框 */
	UPROPERTY()
	UEditableTextBox* NicknameInput;

	/** 密码输入框 */
	UPROPERTY()
	UEditableTextBox* PasswordInput;

	/** 登录按钮 */
	UPROPERTY()
	UButton* LoginBtn;

	/** 进度条 */
	UPROPERTY()
	UCircularThrobber* CircularThrobber;

	/** 信息提示框 */
	UPROPERTY()
	class UPtMessageUserWidget* MessageUserWidget;

};
