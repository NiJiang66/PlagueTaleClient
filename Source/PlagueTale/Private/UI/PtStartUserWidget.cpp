// Fill out your copyright notice in the Description page of Project Settings.


#include "PtStartUserWidget.h"
#include "Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TextBlock.h"

#include "Engine/KBEMain.h"


/** 控件创建完成后初始化方法 */
bool UPtStartUserWidget::Initialize()
{
	if (!Super::Initialize())return false;

	//初始化开始游戏按钮
	StartBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Start")));
	//初始化注册账号按钮
	RegisterBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Register")));
	//初始化退出游戏按钮
	QuitBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_Quit")));

	//初始化版本信息
	clientVersionLabel->SetText(FText::FromString("client version:" + UKBEMain::getClientVersion()));
	clientScriptVersionLabel->SetText(FText::FromString("client script version:" + UKBEMain::getClientScriptVersion()));
	serverVerstionLabel->SetText(FText::FromString("server version:" + UKBEMain::getServerVersion()));
	serverScriptVersionLabel->SetText(FText::FromString("server script version:" + UKBEMain::getServerScriptVersion()));

	//退出游戏按钮点击事件
	QuitBtn->OnClicked.AddDynamic(this, &UPtStartUserWidget::QuitBtnOnClickedEvent);

	return true;
}

/** 退出游戏按钮点击事件 */
void UPtStartUserWidget::QuitBtnOnClickedEvent()
{
	UKismetSystemLibrary::QuitGame(GetWorld(), nullptr, EQuitPreference::Quit, true);
}