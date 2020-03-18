// Fill out your copyright notice in the Description page of Project Settings.


#include "PtChatRoom.h"
#include "SizeBox.h"
#include "ScrollBox.h"
#include "ScrollBoxSlot.h"
#include "Image.h"
#include "EditableText.h"
#include "PtChatItem.h"
#include "Engine/KBEngine.h"
#include "Scripts/PtCommon.h"
#include "Kismet/GameplayStatics.h"



void UPtChatRoom::InstallEvent()
{
	//绑定远程回调方法, 注册了的事件在关卡销毁时一定要注销
	KBENGINE_REGISTER_EVENT("OnAcceptChatList", OnAcceptChatList);
}

void UPtChatRoom::UnInstallEvents()
{
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void UPtChatRoom::SendChatInfo()
{
	//获取输入字符并且清空输入框
	FString Message = InputTextBox->GetText().ToString();
	InputTextBox->SetText(FText());

	//如果输入字符不为空, 发送
	if (!Message.IsEmpty()) {
		UKBEventData_SendChatInfo* EventData = NewObject<UKBEventData_SendChatInfo>();
		EventData->Message = Message;
		KBENGINE_EVENT_FIRE("SendChatInfo", EventData);
	}
	//重新计时隐藏时间，并关闭输入状态
	ResetCounting = true;
	IsWriting = false;
}

void UPtChatRoom::OnAcceptChatList(const UKBEventData* EventData)
{
	ShowOrHideInput(true, false);

	const UKBEventData_OnAcceptChatList* ServerData = Cast<UKBEventData_OnAcceptChatList>(EventData);

	//遍历生成新的ChatItem填充到ScrollBox
	for (auto Info : ServerData->ChatList) {
		UPtChatItem* ChatItem = CreateWidget<UPtChatItem>(this, ChatItemClass);
		ChatItem->InitItem(Info.Name, Info.Date, Info.Message);

		UScrollBoxSlot* ItemSlot = Cast<UScrollBoxSlot>(ChatScrollBox->AddChild(ChatItem));
		ItemSlot->SetHorizontalAlignment(HAlign_Fill);
		ItemSlot->SetVerticalAlignment(VAlign_Bottom);
		ItemSlot->SetPadding(FMargin(0.f, 20.f, 0.f, 0.f));
	}

	//移动滚动栏到最底部
	ChatScrollBox->ScrollToEnd();
}

void UPtChatRoom::ShowOrHideInput(bool IsShow, bool IsWrite)
{
	APlayerController* Controller = UGameplayStatics::GetPlayerController(this, 0);
	if (!Controller) return;

	if (IsShow) {
		//立即显示
		ChatScrollBox->SetVisibility(ESlateVisibility::Visible);
		BgImg->SetVisibility(ESlateVisibility::Visible);

		if (IsWrite) {
			Controller->bShowMouseCursor = true;
			//聚焦到文本输入框
			FInputModeGameAndUI InputMode;
			InputMode.SetWidgetToFocus(InputTextBox->TakeWidget());
			InputMode.SetHideCursorDuringCapture(false);
			InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
			UGameplayStatics::GetPlayerController(this, 0)->SetInputMode(InputMode);

			//修改为输入中
			IsWriting = true;
		}
		else {
			FInputModeGameOnly InputMode;
			InputMode.SetConsumeCaptureMouseDown(false);
			Controller->SetInputMode(InputMode);
			Controller->bShowMouseCursor = false;

			//重新计时隐藏时间
			ResetCounting = true;
		}
	}		
	else {
		//立即隐藏
		ChatScrollBox->SetVisibility(ESlateVisibility::Hidden);
		BgImg->SetVisibility(ESlateVisibility::Hidden);
		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(false);
		Controller->SetInputMode(InputMode);
		Controller->bShowMouseCursor = false;
	}
}
