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

		//注册请求背包数据事件
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqBagList", "ReqBagList", [this](const UKBEventData* EventData)
		{
			pBaseEntityCall->ReqBagList();
		});
		//注册使用物品事件
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReduceGood", "ReduceGood", [this](const UKBEventData* EventData)
		{
			const UKBEventData_ReduceGood* ServerData = Cast<UKBEventData_ReduceGood>(EventData);
			pBaseEntityCall->ReduceGood(ServerData->BagType, ServerData->BlockId);
		});
		//注册移动物品事件
		KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("PassGood", "PassGood", [this](const UKBEventData* EventData)
		{
			const UKBEventData_PassGood* ServerData = Cast<UKBEventData_PassGood>(EventData);
			pBaseEntityCall->PassGood(ServerData->ArcBagType, ServerData->ArcBlockId, ServerData->DesBagType, ServerData->DesBlockId);
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
	PtRoleBase::onBaseHPChanged(oldValue);

	UKBEventData_SetBaseHP* EventData = NewObject<UKBEventData_SetBaseHP>();
	EventData->EntityId = id();
	EventData->IsPlayer = isPlayer();
	EventData->BaseHP = BaseHP;
	//告诉UE4客户端的APtGameMode
	KBENGINE_EVENT_FIRE("SetBaseHP", EventData);
}

void KBEngine::PtRole::onDefenseChanged(int16 oldValue)
{
	PtRoleBase::onDefenseChanged(oldValue);

	UKBEventData_SetDefense* EventData = NewObject<UKBEventData_SetDefense>();
	EventData->EntityId = id();
	EventData->Defense = Defense;
	//告诉UE4客户端的APtGameMode
	KBENGINE_EVENT_FIRE("SetDefense", EventData);
}

void KBEngine::PtRole::onHPChanged(int16 oldValue)
{
	PtRoleBase::onHPChanged(oldValue);

	UKBEventData_SetHP* EventData = NewObject<UKBEventData_SetHP>();
	EventData->EntityId = id();
	EventData->IsPlayer = isPlayer();
	EventData->HP = HP;
	//告诉UE4客户端的APtGameMode
	KBENGINE_EVENT_FIRE("SetHP", EventData);
}

void KBEngine::PtRole::onPowerRatioChanged(float oldValue)
{
	PtRoleBase::onPowerRatioChanged(oldValue);

	UKBEventData_SetPowerRatio* EventData = NewObject<UKBEventData_SetPowerRatio>();
	EventData->EntityId = id();
	EventData->PowerRatio = PowerRatio;
	//告诉UE4客户端的APtGameMode
	KBENGINE_EVENT_FIRE("SetPowerRatio", EventData);
}

void KBEngine::PtRole::onSpeedRatioChanged(float oldValue)
{
	PtRoleBase::onSpeedRatioChanged(oldValue);

	UKBEventData_SetSpeedRatio* EventData = NewObject<UKBEventData_SetSpeedRatio>();
	EventData->EntityId = id();
	EventData->SpeedRatio = SpeedRatio;
	//告诉UE4客户端的APtGameMode
	KBENGINE_EVENT_FIRE("SetSpeedRatio", EventData);
}

void KBEngine::PtRole::OnAttack()
{
	UKBEventData_OnAttack* EventData = NewObject<UKBEventData_OnAttack>();
	EventData->EntityId = id();
	//告诉UE4客户端的APtGameMode,可以播放攻击动画了
	KBENGINE_EVENT_FIRE("OnAttack", EventData);
}

void KBEngine::PtRole::OnIncreaseGood(uint8 arg1, const GOOD_INFO& arg2)
{
	UKBEventData_OnIncreaseGood* EventData = NewObject<UKBEventData_OnIncreaseGood>();
	EventData->BagType = arg1;
	EventData->GoodInfo.InitInfo(arg2.BlockId, arg2.GoodId, arg2.Number);
	//告诉UE4客户端的APtGameWidget
	KBENGINE_EVENT_FIRE("OnIncreaseGood", EventData);
}

void KBEngine::PtRole::OnPassGood(uint8 arg1, const GOOD_INFO& arg2, uint8 arg3, const GOOD_INFO& arg4)
{
	UKBEventData_OnPassGood* EventData = NewObject<UKBEventData_OnPassGood>();
	EventData->ArcBagType = arg1;
	EventData->ArcGoodInfo.InitInfo(arg2.BlockId, arg2.GoodId, arg2.Number);
	EventData->DesBagType = arg3;
	EventData->DesGoodInfo.InitInfo(arg4.BlockId, arg4.GoodId, arg4.Number);
	//告诉UE4客户端的APtGameWidget
	KBENGINE_EVENT_FIRE("OnPassGood", EventData);
}

void KBEngine::PtRole::OnReduceGood(uint8 arg1, uint8 arg2, const GOOD_INFO& arg3)
{
	UKBEventData_OnReduceGood* EventData = NewObject<UKBEventData_OnReduceGood>();
	EventData->ReduceRes = arg1;
	EventData->BagType = arg2;
	EventData->GoodInfo.InitInfo(arg3.BlockId, arg3.GoodId, arg3.Number);
	//告诉UE4客户端的APtGameWidget
	KBENGINE_EVENT_FIRE("OnReduceGood", EventData);
}

void KBEngine::PtRole::OnReqBagList(const BAG_INFO& arg1, const BAG_INFO& arg2, const BAG_INFO& arg3, const BAG_INFO& arg4)
{
	UKBEventData_OnReqBagList* EventData = NewObject<UKBEventData_OnReqBagList>();

	for (auto Info : arg1.Value) {
		FGOOD_INFO GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		EventData->MainBag.Add(GoodInfo);
	}
	for (auto Info : arg2.Value) {
		FGOOD_INFO GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		EventData->SkillBag.Add(GoodInfo);
	}
	for (auto Info : arg3.Value) {
		FGOOD_INFO GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		EventData->BuffBag.Add(GoodInfo);
	}
	for (auto Info : arg4.Value) {
		FGOOD_INFO GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		EventData->EquipBag.Add(GoodInfo);
	}

	KBENGINE_EVENT_FIRE("OnReqBagList", EventData);
}

