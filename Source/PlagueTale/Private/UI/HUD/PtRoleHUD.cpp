// Fill out your copyright notice in the Description page of Project Settings.


#include "PtRoleHUD.h"
#include "PtRoleUserWidget.h"

void APtRoleHUD::BeginPlay()
{
	RoleWidget = CreateWidget<UPtRoleUserWidget>(GetWorld(), RoleWidgetClass);
	if (RoleWidget) {
		RoleWidget->AddToViewport();
	}
}
