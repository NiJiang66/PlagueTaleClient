// Fill out your copyright notice in the Description page of Project Settings.


#include "PtRoomItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"

bool UPtRoomItem::Initialize()
{
	if (!Super::Initialize())return false;

	//注册按钮点击事件
	ItemBtn->OnClicked.AddDynamic(this, &UPtRoomItem::ItemButtonEvent);

	return true;
}

void UPtRoomItem::ItemButtonEvent()
{
	RoomItemSelectDel.ExecuteIfBound(RoomInfo.RoomId);
}

void UPtRoomItem::InitItem(FROOM_INFO InRoomInfo)
{
	RoomInfo = InRoomInfo;
	ItemName->SetText(FText::FromString(InRoomInfo.Name));
}

void UPtRoomItem::ItemSelect()
{
	IsSelected = true;
	OutLineImg->SetVisibility(ESlateVisibility::Visible);
}

void UPtRoomItem::UnItemSelect()
{
	IsSelected = false;
	OutLineImg->SetVisibility(ESlateVisibility::Collapsed);
}
