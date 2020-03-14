// Fill out your copyright notice in the Description page of Project Settings.


#include "PtPlayerController.h"

void APtPlayerController::BeginPlay()
{
	Super::BeginPlay();
}

void APtPlayerController::SwitchInputMode(bool IsShowMouse)
{
	if (IsShowMouse) {
		bShowMouseCursor = true;

		FInputModeGameAndUI InputMode;
		InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::DoNotLock);
		InputMode.SetHideCursorDuringCapture(false);//鼠标按下时不显示鼠标
		SetInputMode(InputMode);
	}
	else {
		bShowMouseCursor = false;

		FInputModeGameOnly InputMode;
		InputMode.SetConsumeCaptureMouseDown(false);
		SetInputMode(InputMode);
	}
}
