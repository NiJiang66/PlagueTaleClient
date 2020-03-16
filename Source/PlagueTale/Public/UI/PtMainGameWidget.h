﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PtDataMgr.h"
#include "PtMainGameWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UOverlay;
class UKBEventData;
class UPtSkillBag;
class UPtBuffBag;
class UPtEquipBag;
class UPtMainBag;
class APtPlayerCharacter;

/**
 * 主游戏关卡界面
 */
UCLASS()
class PLAGUETALE_API UPtMainGameWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	/**	复活 */
	UFUNCTION(BlueprintCallable)
	void ReliveEvent();

	/**	绑定事件 */
	void InstallEvents(FText RoomName);
	/**	卸载事件 */
	void UnInstallEvents();

public:

	/**	设置玩家名字显示 */
	void SetName(FString InName);
	/**	设置血量百分比显示 */
	void SetHPPercent(float InPercent);
	/**	设置防御值显示 */
	void SetDefense(int32 InDefense);
	/**	设置力量值显示 */
	void SetPowerRatio(float InPowerRatio);
	/**	设置速度值显示 */
	void SetSpeedRatio(float InSpeedRatio);

public:

	void OnReqBagList(const UKBEventData* EventData);

	void OnIncreaseGood(const UKBEventData* EventData);

	void OnPassGood(const UKBEventData* EventData);

	void OnReduceGood(const UKBEventData* EventData);

	/**	通知背包更新某个格子的数据 */
	void UpdateBagBlock(EBagType BagType, uint8 BlockId);
	   

public:
	UPROPERTY()
	APtPlayerCharacter* PlayerCharacter;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* NameText;

	UPROPERTY(Meta = (BindWidget))
	UTextBlock* RoomText;

	UPROPERTY(Meta = (BindWidget))
	UProgressBar* BloodProgress;

	UPROPERTY(Meta = (BindWidget))
	UOverlay* ReliveBox;

	UPROPERTY(Meta = (BindWidget))
	UPtSkillBag* SkillBag;

	UPROPERTY(Meta = (BindWidget))
	UPtBuffBag* BuffBag;

	UPROPERTY(Meta = (BindWidget))
	UPtEquipBag* EquipBag;

	UPROPERTY(Meta = (BindWidget))
	UPtMainBag* MainBag;
};
