// Fill out your copyright notice in the Description page of Project Settings.


#include "PtGameHUD.h"
#include "PtMainGameWidget.h"
#include "PTGameInstance.h"
#include "Kismet/GameplayStatics.h"

void APtGameHUD::BeginPlay()
{
	Super::BeginPlay();
	InitUI();
}

void APtGameHUD::InitUI()
{
	if (RoleWidget == nullptr) {
		RoleWidget = CreateWidget<UPtMainGameWidget>(GetWorld(), RoleWidgetClass);
		if (RoleWidget) {
			RoleWidget->AddToViewport();
			//注册KBE事件以及设置房间名
			UPTGameInstance* GameInstance = Cast<UPTGameInstance>(UGameplayStatics::GetGameInstance(this));
			RoleWidget->InstallEvents(GameInstance->RoomName);
		}
	}
}
