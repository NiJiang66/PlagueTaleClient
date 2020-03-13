// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlay/GameMode/PtGameModeBase.h"
#include "PtRoomGameMode.generated.h"

class UKBEventData;

/**
 * 选择房间游戏模式
 */
UCLASS()
class PLAGUETALE_API APtRoomGameMode : public APtGameModeBase
{
	GENERATED_BODY()
public:

	/**	安装登陆时需要监听的KBE事件 */
	virtual void InstallEvents() override;

	/**	玩家进入游戏场景 */
	void AddSpaceGeometryMapping(const UKBEventData* EventData);

protected:

	//客户端的实现，对应PtAccount下的回调函数，在InstallEvents下注册
	/**	KBE事件，请求房间列表回调函数的回调函数 */
	void OnReqRoomList(const UKBEventData* EventData);
	/**	KBE事件，创建房间回调函数的回调函数 */
	void OnCreateRoom(const UKBEventData* EventData);

};
