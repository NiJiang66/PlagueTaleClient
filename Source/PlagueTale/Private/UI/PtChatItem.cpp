// Fill out your copyright notice in the Description page of Project Settings.


#include "PtChatItem.h"
#include "TextBlock.h"

void UPtChatItem::InitItem(FString Name, FString Date, FString Message)
{
	FString UserItem = FString::Printf(TEXT("%s   %s  :"), *Date, *Name);
	UserText->SetText(FText::FromString(UserItem));

	InfoText->SetText(FText::FromString(Message));

	//进入隐藏流程
	DisappearProcess();
}
