// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "PtRoomHUD.generated.h"

class UPtRoomWidget;

/**
 * 房间模式HUD
 */
UCLASS()
class PLAGUETALE_API APtRoomHUD : public AHUD
{
	GENERATED_BODY()
public:
	virtual void BeginPlay() override;

public:

	/** 选择角色界面的类型和指针 */
	UPROPERTY(EditAnywhere)
		TSubclassOf<UPtRoomWidget> RoomWidgetClass;
	UPROPERTY()
		UPtRoomWidget* RoomWidget;
};
