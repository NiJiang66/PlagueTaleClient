// Fill out your copyright notice in the Description page of Project Settings.


#include "PtStartHUD.h"
#include "PtStartUserWidget.h"
#include "PtRegisterUserWidget.h"
#include "PtLoginUserWidget.h"
#include "Button.h"


APtStartHUD::APtStartHUD()
{

}

/** 游戏开始调用的方法 */
void APtStartHUD::BeginPlay()
{
	Super::BeginPlay();	

	StartWidget = CreateWidget<UPtStartUserWidget>(GetWorld(), StartWidgetClass);
	LoginWidget = CreateWidget<UPtLoginUserWidget>(GetWorld(), LoginWidgetClass);
	RegisterWidget = CreateWidget<UPtRegisterUserWidget>(GetWorld(), RegisterWidgetClass);

	if (StartWidget&&LoginWidget&&RegisterWidget) {
		//显示到屏幕
		StartWidget->AddToViewport();

		//开始游戏按钮的点击事件
		StartWidget->StartBtn->OnClicked.AddDynamic(this, &APtStartHUD::StartBtnOnClickedEvent);
		//注册账号按钮的点击事件
		StartWidget->RegisterBtn->OnClicked.AddDynamic(this, &APtStartHUD::RegisterBtnOnClickedEvent);

		//设置登录界面返回按钮的点击事件
		LoginWidget->BackBtn->OnClicked.AddDynamic(this, &APtStartHUD::LoginBackBtnOnClickedEvent);

		//设置注册界面返回按钮的点击事件
		RegisterWidget->BackBtn->OnClicked.AddDynamic(this, &APtStartHUD::RegisterBackBtnOnClickedEvent);
	}
}

/** 开始游戏按钮点击事件 */
void APtStartHUD::StartBtnOnClickedEvent()
{
	if (StartWidget&&LoginWidget) {
		//游戏开始界面从视口中移除
		StartWidget->RemoveFromViewport();
		//登录游戏界面添加到视口
		LoginWidget->AddToViewport();
	}
}

/** 注册账号按钮点击事件 */
void APtStartHUD::RegisterBtnOnClickedEvent()
{
	if (StartWidget&&LoginWidget) {
		//游戏开始界面从视口中移除
		StartWidget->RemoveFromViewport();
		//注册账号界面添加到视口中
		RegisterWidget->AddToViewport();
	}
}

/** 登录页面返回按钮点击事件 */
void APtStartHUD::LoginBackBtnOnClickedEvent()
{
	if (StartWidget&&LoginWidget) {
		//登录账号界面从视口中移除 
		LoginWidget->RemoveFromViewport();
		//游戏开始界面添加到视口当中
		StartWidget->AddToViewport();
	}
}

/** 注册页面返回按钮点击事件 */
void APtStartHUD::RegisterBackBtnOnClickedEvent()
{
	if (StartWidget&&LoginWidget) {
		//注册账号界面从视口中移除
		RegisterWidget->RemoveFromViewport();
		//游戏开始界面添加到视口当中
		StartWidget->AddToViewport();
	}
}
