#include "PtMonster.h"
#include "Engine/KBEvent.h"
#include "Engine/KBEngine.h"
#include "Scripts/PtCommon.h"
#include "Scripts/PtEventData.h"


KBEngine::PtMonster::PtMonster()
{

}

KBEngine::PtMonster::~PtMonster()
{

}

void KBEngine::PtMonster::__init__()
{

}

void KBEngine::PtMonster::onDestroy()
{
	//注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void KBEngine::PtMonster::OnAnimUpdate(const ANIM_INFO& arg1)
{
	UKBEventData_OnAnimUpdate* EventData = NewObject<UKBEventData_OnAnimUpdate>();
	EventData->EntityId = id();
	EventData->Speed = arg1.Speed;
	EventData->Direction = arg1.Direction;
	//告诉UE4客户端的APtGameMode
	KBENGINE_EVENT_FIRE("OnAnimUpdate", EventData);
}

void KBEngine::PtMonster::onBaseHPChanged(int16 oldValue)
{
	UKBEventData_SetBaseHP* EventData = NewObject<UKBEventData_SetBaseHP>();
	EventData->EntityId = id();
	EventData->IsPlayer = isPlayer();
	EventData->BaseHP = BaseHP;
	//告诉UE4客户端的APtGameMode
	KBENGINE_EVENT_FIRE("SetBaseHP", EventData);
}

void KBEngine::PtMonster::onHPChanged(int16 oldValue)
{
	UKBEventData_SetHP* EventData = NewObject<UKBEventData_SetHP>();
	EventData->EntityId = id();
	EventData->IsPlayer = isPlayer();
	EventData->HP = HP;
	//告诉UE4客户端的APtGameMode
	KBENGINE_EVENT_FIRE("SetHP", EventData);
}

