#include "PtRole.h"
#include "Engine/KBEvent.h"
#include "Engine/KBEngine.h"
#include "Scripts/PtCommon.h"
#include "Scripts/PtEventData.h"

KBEngine::PtRole::PtRole()
{

}

KBEngine::PtRole::~PtRole()
{

}

void KBEngine::PtRole::__init__()
{
	// 如果是本地玩家
	if (isPlayer()) {
		//注册动作同步事件
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("AnimUpdate", "AnimUpdate", [this](const UKBEventData* EventData) {
			const UKBEventData_AnimUpdate* ServerData = Cast<UKBEventData_AnimUpdate>(EventData);
			ANIM_INFO AnimInfo;
			AnimInfo.Speed = ServerData->Speed;
			AnimInfo.Direction = ServerData->Direction;
			pCellEntityCall->AnimUpdate(AnimInfo);
		});
		//注册复活事件
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("Relive", "Relive", [this](const UKBEventData* EventData)
		{
			pCellEntityCall->Relive();
		});
	}
}

void KBEngine::PtRole::onDestroy()
{
	//注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void KBEngine::PtRole::OnAnimUpdate(const ANIM_INFO& arg1)
{
	UKBEventData_OnAnimUpdate* EventData = NewObject<UKBEventData_OnAnimUpdate>();
	EventData->EntityId = id();
	EventData->Speed = arg1.Speed;
	EventData->Direction = arg1.Direction;
	//告诉UE4客户端的APtGameMode
	KBENGINE_EVENT_FIRE("OnAnimUpdate", EventData);
}

void KBEngine::PtRole::onBaseHPChanged(int16 oldValue)
{
	UKBEventData_SetBaseHP* EventData = NewObject<UKBEventData_SetBaseHP>();
	EventData->EntityId = id();
	EventData->IsPlayer = isPlayer();
	EventData->BaseHP = BaseHP;
	//告诉UE4客户端的APtGameMode
	KBENGINE_EVENT_FIRE("SetBaseHP", EventData);
}

void KBEngine::PtRole::onHPChanged(int16 oldValue)
{
	UKBEventData_SetHP* EventData = NewObject<UKBEventData_SetHP>();
	EventData->EntityId = id();
	EventData->IsPlayer = isPlayer();
	EventData->HP = HP;
	//告诉UE4客户端的APtGameMode
	KBENGINE_EVENT_FIRE("SetHP", EventData);
}

void KBEngine::PtRole::OnAttack()
{
	UKBEventData_OnAttack* EventData = NewObject<UKBEventData_OnAttack>();
	EventData->EntityId = id();
	//告诉UE4客户端的APtGameMode,可以播放攻击动画了
	KBENGINE_EVENT_FIRE("OnAttack", EventData);
}

