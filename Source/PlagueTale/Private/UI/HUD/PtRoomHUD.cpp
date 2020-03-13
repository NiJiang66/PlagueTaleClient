// Fill out your copyright notice in the Description page of Project Settings.


#include "PtRoomHUD.h"
#include "PtRoomWidget.h"

void APtRoomHUD::BeginPlay()
{
	Super::BeginPlay();

	RoomWidget = CreateWidget<UPtRoomWidget>(GetWorld(), RoomWidgetClass);
	if (RoomWidget) {
		RoomWidget->AddToViewport();
		//创建之后直接初始化
		RoomWidget->RefreshRoomListEvent();
	}
}
