// Fill out your copyright notice in the Description page of Project Settings.


#include "PtStartHUD.h"
#include "PtStartUserWidget.h"
#include "PtRegisterUserWidget.h"
#include "PtLoginUserWidget.h"
#include "Button.h"
#include "ConstructorHelpers.h"
#include "Engine/Engine.h"


APtStartHUD::APtStartHUD()
{	
	//加载游戏开始Widget
	static ConstructorHelpers::FClassFinder<UPtStartUserWidget> PTStartUserWidget(
		TEXT("WidgetBlueprint'/Game/UI/PTStartUserWidget_BP.PTStartUserWidget_BP_C'")
	);
	StartWidget = CreateWidget<UPtStartUserWidget>(GetWorld(), PTStartUserWidget.Class);

	//加载游戏登录Widget
	static ConstructorHelpers::FClassFinder<UPtLoginUserWidget> PTLoginUserWidget(
		TEXT("WidgetBlueprint'/Game/UI/PTLoginUserWidget_BP.PTLoginUserWidget_BP_C'")
	);
	LoginWidget = CreateWidget<UPtLoginUserWidget>(GetWorld(), PTLoginUserWidget.Class);

	//加载注册账号Widget
	static ConstructorHelpers::FClassFinder<UPtRegisterUserWidget> PTRegisterUserWidget(
		TEXT("WidgetBlueprint'/Game/UI/PTRegisterUserWidget_BP.PTRegisterUserWidget_BP_C'")
	);
	RegisterWidget = CreateWidget<UPtRegisterUserWidget>(GetWorld(), PTRegisterUserWidget.Class);

}

/** 游戏开始调用的方法 */
void APtStartHUD::BeginPlay()
{
	Super::BeginPlay();	
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

/** 开始游戏按钮点击事件 */
void APtStartHUD::StartBtnOnClickedEvent()
{
	//游戏开始界面从视口中移除
	StartWidget->RemoveFromViewport();
	//登录游戏界面添加到视口
	LoginWidget->AddToViewport();
}

/** 注册账号按钮点击事件 */
void APtStartHUD::RegisterBtnOnClickedEvent()
{
	//游戏开始界面从视口中移除
	StartWidget->RemoveFromViewport();
	//注册账号界面添加到视口中
	RegisterWidget->AddToViewport();
}

/** 登录页面返回按钮点击事件 */
void APtStartHUD::LoginBackBtnOnClickedEvent()
{
	//登录账号界面从视口中移除 
	LoginWidget->RemoveFromViewport();
	//游戏开始界面添加到视口当中
	StartWidget->AddToViewport();
}

/** 注册页面返回按钮点击事件 */
void APtStartHUD::RegisterBackBtnOnClickedEvent()
{
	//注册账号界面从视口中移除
	RegisterWidget->RemoveFromViewport();
	//游戏开始界面添加到视口当中
	StartWidget->AddToViewport();
}
