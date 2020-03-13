// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PtRoleHUD.generated.h"


class UPtRoleUserWidget;

/**
 * 角色选择界面HUD
 */
UCLASS()
class PLAGUETALE_API APtRoleHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

public:

	/** 选择角色界面的类型和指针 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPtRoleUserWidget> RoleWidgetClass;
	UPROPERTY()
	UPtRoleUserWidget* RoleWidget;
};
