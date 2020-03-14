// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PtPlayerController.generated.h"

/**
 * 主要游戏场景玩家控制器
 */
UCLASS()
class PLAGUETALE_API APtPlayerController : public APlayerController
{
	GENERATED_BODY()
protected:
	virtual void BeginPlay() override;

public:
	/**	切换输入模式 */
	void SwitchInputMode(bool IsShowMouse);

};
