// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlay/GameMode/PtGameModeBase.h"
#include "Scripts/PtEventData.h"
#include "PtRoleGameMode.generated.h"


class APtRenderActor;


/**
 * 选择角色游戏模式(选角界面)
 */
UCLASS()
class PLAGUETALE_API APtRoleGameMode : public APtGameModeBase
{
	GENERATED_BODY()
public:
	APtRoleGameMode();

	/**	安装登陆时需要监听的KBE事件 */
	virtual void InstallEvents() override;

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;


	//三个给UI调用的方法
	/**	请求创建新角色 */
	void ReqCreateRole(uint8 RoleType, const FString& Name);
	/**	请求移除角色 */
	void ReqRemoveRole(const FROLE_INFO& RoleInfo);
	/**	选择角色进入游戏 */
	void SelectRoleGame(const FROLE_INFO& RoleInfo);

protected:

	virtual void BeginPlay() override;

	//客户端的实现，对应PtAccount下的回调函数，在InstallEvents下注册
	/**	KBE事件，请求角色列表回调函数的回调函数 */
	void OnReqRoleList(const UKBEventData* EventData);
	/**	KBE事件，创建角色结果回调函数的回调函数 */
	void OnCreateRoleResult(const UKBEventData* EventData);
	/**	KBE事件，移除角色回调函数的回调函数 */
	void OnRemoveRole(const UKBEventData* EventData);
	/**	KBE事件，选择角色进入游戏回调函数的回调函数 */
	void OnSelectRoleGame(const UKBEventData* EventData);



public:
	/**	渲染角色到RenderTexture的场景Actor */
	APtRenderActor* RenderActor;

};
