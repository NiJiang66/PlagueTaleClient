// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PtStartController.generated.h"

/**
 * 开始控制器(登录和选择角色界面)
 */
UCLASS()
class PLAGUETALE_API APtStartController : public APlayerController
{
	GENERATED_BODY()

protected:

	virtual void BeginPlay() override;

};
