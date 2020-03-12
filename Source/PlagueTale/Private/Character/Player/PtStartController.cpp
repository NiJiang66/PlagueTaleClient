// Fill out your copyright notice in the Description page of Project Settings.


#include "PtStartController.h"
//#include "Scripts/PtCommon.h"

void APtStartController::BeginPlay()
{
	Super::BeginPlay();

	//命令行设置游戏窗口
	ConsoleCommand("r.setres 960x540w");

	bShowMouseCursor = true;

	FInputModeUIOnly InputMode;
	InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
	SetInputMode(InputMode);
}
