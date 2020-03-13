// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PtStartHUD.generated.h"

class UPtStartUserWidget;
class UPtLoginUserWidget;
class UPtRegisterUserWidget;


/**
 * 开始(登录注册)界面HUD
 */
UCLASS()
class PLAGUETALE_API APtStartHUD : public AHUD
{
	GENERATED_BODY()

public:

	APtStartHUD();

	virtual void BeginPlay() override;

	/** 开始游戏按钮点击事件 */
	UFUNCTION()
	void StartBtnOnClickedEvent();

	/** 注册账号按钮点击事件 */
	UFUNCTION()
	void RegisterBtnOnClickedEvent();

	/** 登录页面返回按钮点击事件 */
	UFUNCTION()
	void LoginBackBtnOnClickedEvent();

	/** 注册页面返回按钮点击事件 */
	UFUNCTION()
	void RegisterBackBtnOnClickedEvent();

public:

	/** 游戏开始界面 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPtStartUserWidget> StartWidgetClass;
	UPROPERTY()
	UPtStartUserWidget* StartWidget;

	/** 游戏登录界面 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPtLoginUserWidget> LoginWidgetClass;
	UPROPERTY()
	UPtLoginUserWidget* LoginWidget;

	/** 游戏注册界面 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPtRegisterUserWidget> RegisterWidgetClass;
	UPROPERTY()
	UPtRegisterUserWidget* RegisterWidget;



};
