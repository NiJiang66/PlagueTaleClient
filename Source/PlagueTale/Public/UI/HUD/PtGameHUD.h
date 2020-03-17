// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PtGameHUD.generated.h"

class UPtMainGameWidget;

/**
 * 游戏HUD
 */
UCLASS()
class PLAGUETALE_API APtGameHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

	void InitActorAndUI();

public:

	/** 主游戏关卡界面的类型和指针 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPtMainGameWidget> RoleWidgetClass;
	UPROPERTY()
	UPtMainGameWidget* MainGameWidget;
};
