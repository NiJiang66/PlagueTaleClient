// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
//#include "Scripts/PtEventData.h"
#include "PtGameModeBase.generated.h"

class UKBEventData;

/**
 * 游戏模式基类
 */
UCLASS()
class PLAGUETALE_API APtGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:

	APtGameModeBase();

	/** Called once this actor has been deleted */
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason)override;

	/**	安装登陆时需要监听的KBE事件 */
	virtual void InstallEvents();
	/**	注销进入场景时注册的KBE事件 */
	virtual void UnInstallEvents();

	/**	KBE事件,玩家被踢出服务器 */
	virtual void OnKicked(const UKBEventData* pEventData);
	/**	KBE事件,断线时 */
	virtual void OnDisconnected(const UKBEventData* pEventData);
	/**	KBE事件,当前连接状态 */
	virtual void OnConnectionState(const UKBEventData* pEventData);
	/**	KBE事件,断线重连 */
	virtual void OnReloginBaseappSuccessfully(const UKBEventData* pEventData);
	/**	KBE事件,重连失败 */
	virtual void OnReloginBaseappFailed(const UKBEventData* pEventData);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	/**	开始重新登录Baseapp，不是Loginapp，因为登录之后会把数据转移到Baseapp */
	void StartReloginBaseappTimer();
	/**	停止重新登录Baseapp */
	void StopReloginBaseappTimer();

	/**	重登baseapp项目，绑定给定时器的事件 */
	void OnReloginBaseappTimer();


protected:

	/**	定时器 */
	FTimerHandle TimerHandle;

	bool StartRelogin;

};
