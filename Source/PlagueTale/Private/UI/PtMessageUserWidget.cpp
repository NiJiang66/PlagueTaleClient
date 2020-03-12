// Fill out your copyright notice in the Description page of Project Settings.


#include "PtMessageUserWidget.h"
#include "TextBlock.h"
#include "Button.h"


bool UPtMessageUserWidget::Initialize()
{
	if (!Super::Initialize())return false;

	//创建文本框
	MsgBlock = Cast<UTextBlock>(GetWidgetFromName(TEXT("TextBlock_Message")));

	//创建关闭按钮
	CloseBtn = Cast<UButton>(GetWidgetFromName(TEXT("Button_MessageClose")));
	//设置关闭按钮得回调
	CloseBtn->OnClicked.AddDynamic(this, &UPtMessageUserWidget::ClosButtonOnClickedEvent);

	return true;
}

/* 设置关闭按钮事件*/
void UPtMessageUserWidget::ClosButtonOnClickedEvent()
{
	this->SetVisibility(ESlateVisibility::Hidden);
}
