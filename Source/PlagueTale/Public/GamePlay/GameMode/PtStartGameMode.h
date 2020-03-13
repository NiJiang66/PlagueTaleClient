// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PtGameModeBase.h"
#include "PtStartGameMode.generated.h"

class UKBEMain;

/**
 * 开始游戏模式(登录界面)
 */
UCLASS()
class PLAGUETALE_API APtStartGameMode : public APtGameModeBase
{
	GENERATED_BODY()
public:
	/**	插件的入口模块 */
	UKBEMain* KBEMain;
public:

	APtStartGameMode();

	/**	安装登陆时需要监听的KBE事件 */
	virtual void InstallEvents();

	/**	KBE事件，创建账户的回调函数  */
	void OnCreateAccountResult(const UKBEventData* pEventData);
	/**	KBE事件，登录失败的回调函数  */
	void OnLoginFailed(const UKBEventData* pEventData);
	/**	KBE事件，客户端版本不匹配的回调函数  */
	void OnVersionNotMatch(const UKBEventData* pEventData);
	/**	KBE事件，脚本不匹配的回调函数  */
	void OnScriptVersionNotMatch(const UKBEventData* pEventData);
	/**	KBE事件，登录Baseapp失败的回调函数  */
	void OnLoginBaseappFailed(const UKBEventData* pEventData);
	/**	KBE事件，登录成功的回调函数  */
	void OnLoginSuccessfully(const UKBEventData* pEventData);
	/**	KBE事件，登录Baseapp的回调函数  */
	void OnLoginBaseapp(const UKBEventData* pEventData);
	/**	KBE事件  */
	void Loginapp_importClientMessages(const UKBEventData* pEventData);
	/**	KBE事件  */
	void Baseapp_importClientMessages(const UKBEventData* pEventData);
	/**	KBE事件  */
	void Baseapp_importClientEntityDef(const UKBEventData* pEventData);

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


};
