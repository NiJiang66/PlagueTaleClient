// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PtMainGameWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UOverlay;

/**
 * 主游戏关卡界面
 */
UCLASS()
class PLAGUETALE_API UPtMainGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:

	/**	绑定事件 */
	void InstallEvents(FText RoomName);

	/**	卸载事件 */
	void UnInstallEvents();

	/**	设置玩家名字 */
	void SetName(FString InName);

	/**	设置血量百分比 */
	void SetHPPercent(float InPercent);

	/**	复活 */
	UFUNCTION(BlueprintCallable)
	void ReliveEvent();


public:

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* RoomText;

	UPROPERTY(Meta = (BindWidget))
	UProgressBar* BloodProgress;

	UPROPERTY(Meta = (BindWidget))
	UOverlay* ReliveBox;
	
};
