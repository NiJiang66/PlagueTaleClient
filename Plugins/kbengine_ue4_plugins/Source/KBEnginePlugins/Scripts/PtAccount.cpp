#include "PtAccount.h"
#include "PtEventData.h"
#include "Engine/KBEngine.h"
#include "Scripts/PtCommon.h"

KBEngine::PtAccount::PtAccount()
{

}

KBEngine::PtAccount::~PtAccount()
{

}

void KBEngine::PtAccount::__init__()
{
	//注册客户端请求事件，这些事件是用于在PtRoleGameMode通过KBENGINE_EVENT_FIRE宏触发事件时可以调用到这里注册的函数
	RegisterClientReqEvent();

	//触发登录成功事件
	UKBEventData_onLoginSuccessfully* EventData = NewObject<UKBEventData_onLoginSuccessfully>();
	EventData->entity_uuid = KBEngineApp::getSingleton().entity_uuid();
	EventData->entity_id = id();
	KBENGINE_EVENT_FIRE("onLoginSuccessfully", EventData);//在APtStartGameMode::InstallEvents()里注册
	PtH::Debug() << "PtAccount::__init__ and Fire 'onLoginSuccessfully' Event" << PtH::Endl();

	//向服务端请求获取角色列表
	pBaseEntityCall->ReqRoleList();
}

void KBEngine::PtAccount::onDestroy()
{
	//注销该对象注册的所有事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void KBEngine::PtAccount::OnReqRoleList(const ROLE_LIST& arg1)
{
	UKBEventData_OnReqRoleList* EventData = NewObject<UKBEventData_OnReqRoleList>();
	for (auto& arg : arg1.Value) {
		//保存角色信息列表到本地
		ROLE_INFO LocalInfo;
		LocalInfo.Dbid = arg.Dbid;
		LocalInfo.Name = arg.Name;
		LocalInfo.RoleType = arg.RoleType;
		LocalInfo.Data.DataType = arg.Data.DataType;
		LocalInfo.Data.DataValue = arg.Data.DataValue;
		RoleList.Value.Add(LocalInfo);

		//保存角色列表到OnReqRoleList事件的数据类
		FROLE_INFO RoleInfo;
		RoleInfo.InitData(arg.Dbid, arg.Name, arg.RoleType, (LastSelRole == arg.Dbid));
		EventData->RoleList.Add(RoleInfo);
	}
	//告诉UE4客户端相应的GameMode
	KBENGINE_EVENT_FIRE("OnReqRoleList", EventData);
}

void KBEngine::PtAccount::OnCreateRoleResult(uint8 arg1, const ROLE_INFO& arg2)
{
	UKBEventData_OnCreateRoleResult* EventData = NewObject<UKBEventData_OnCreateRoleResult>();
	EventData->RoleInfo.InitData(arg2.Dbid, arg2.Name, arg2.RoleType, (LastSelRole == arg2.Dbid));

	//设置结果信息
	EventData->ErrorCode = arg1;

	switch (arg1)
	{
	case 0:
		//为0表示创建成功,将数据存储到本地
		RoleList.Value.Push(arg2);
		break;
	case 1:
		//为1表示有名字重复
		EventData->ErrorStr = TEXT("Repetition Name");
		PtH::Debug() << "PtAccount::OnCreateRoleResult : Repetition Name --> " << arg2.Name << PtH::Endl();
		break;
	case 2:
		//为2表示有类型重复
		EventData->ErrorStr = TEXT("Repetition RoleType");
		PtH::Debug() << "PtAccount::OnCreateRoleResult : Repetition RoleType --> " << arg2.RoleType << PtH::Endl();
		break;
	default:
		PtH::Debug() << "PtAccount::OnCreateRoleResult : ErrorCode unknow --> " << arg1 << PtH::Endl();
		break;
	}
	//告诉UE4客户端相应的GameMode
	KBENGINE_EVENT_FIRE("OnCreateRoleResult", EventData);
}

void KBEngine::PtAccount::OnRemoveRole(uint64 arg1)
{
	int InfoIndex = -1;
	for (int i = 0; i < RoleList.Value.Num(); ++i) {
		if (RoleList.Value[i].Dbid == arg1) {
			InfoIndex = i;
			break;
		}
	}

	//如果没找到, 找不到的情况应该不存在
	if (InfoIndex < 0) {
		PtH::Debug() << "PtAccount::OnRemoveRole : Did not found the role by Dbid --> " << arg1 << PtH::Endl();
		return;
	}

	UKBEventData_OnRemoveRole* EventData = NewObject<UKBEventData_OnRemoveRole>();
	EventData->RoleInfo.InitData(RoleList.Value[InfoIndex].Dbid, RoleList.Value[InfoIndex].Name, RoleList.Value[InfoIndex].RoleType, (LastSelRole == RoleList.Value[InfoIndex].Dbid));

	//从本地列表移除角色
	RoleList.Value.RemoveAt(InfoIndex);
	//告诉UE4客户端相应的GameMode相应的GameMode
	KBENGINE_EVENT_FIRE("OnRemoveRole", EventData);
}

void KBEngine::PtAccount::OnSelectRoleGame(uint8 arg1, uint64 arg2)
{
	//判定结果, 如果不为1就可以跳转界面
	if (arg1 == 1)	{
		//选择角色不存在
		PtH::Debug() << "PtAccount::OnSelectRoleGame No Role By Dbid --> " << arg2 << PtH::Endl();
		return;
	}

	UKBEventData_OnSelectRoleGame* EventData = NewObject<UKBEventData_OnSelectRoleGame>();
	EventData->Dbid = arg2;
	//告诉UE4客户端相应的GameMode创建房间成功
	KBENGINE_EVENT_FIRE("OnSelectRoleGame", EventData);
}

void KBEngine::PtAccount::OnReqRoomList(const ROOM_LIST& arg1)
{
	UKBEventData_OnReqRoomList* EventData = NewObject<UKBEventData_OnReqRoomList>();
	for (auto& arg : arg1.Value) {
		FROOM_INFO RoomInfo;
		RoomInfo.InitData(arg.RoomId, arg.Name);
		EventData->RoomList.Add(RoomInfo);
	}
	//告诉UE4客户端请求房间列表成功
	KBENGINE_EVENT_FIRE("OnReqRoomList", EventData);
}

void KBEngine::PtAccount::OnCreateRoom(uint8 arg1, const ROOM_INFO& arg2)
{
	if (arg1 == 1) {
		//如果创建失败
		PtH::Debug() << "PtAccount::OnCreateRoom() Faild By Name : " << arg2.Name << PtH::Endl();
		return;
	}
	UKBEventData_OnCreateRoom* EventData = NewObject<UKBEventData_OnCreateRoom>();
	EventData->RoomInfo.InitData(arg2.RoomId, arg2.Name);
	//告诉UE4客户端创建房间成功
	KBENGINE_EVENT_FIRE("OnCreateRoom", EventData);
}

void KBEngine::PtAccount::ReqCreateRole(uint8 RoleType, const FString& Name)
{
	PtH::Debug() << "PtAccount::ReqCreateRole(): RoleType --> " << RoleType << " ; Name --> " << Name << PtH::Endl();
	pBaseEntityCall->ReqCreateRole(RoleType, Name);
}

void KBEngine::PtAccount::ReqRemoveRole(const FString& Name)
{
	PtH::Debug() << "PtAccount::RegRemoveRole(): Name --> " << Name << PtH::Endl();
	pBaseEntityCall->ReqRemoveRole(Name);
}

void KBEngine::PtAccount::SelectRoleGame(uint64 Dbid)
{
	PtH::Debug() << "PtAccount::ReqSelectRoleGame(): Dbid --> " << Dbid << PtH::Endl();
	pBaseEntityCall->ReqSelectRoleGame(Dbid);
}

void KBEngine::PtAccount::ReqRoomList()
{
	PtH::Debug() << "PtAccount::ReqRoomList()" << PtH::Endl();
	pBaseEntityCall->ReqRoomList();
}

void KBEngine::PtAccount::ReqCreateRoom(const FString& Name)
{
	PtH::Debug() << "PtAccount::ReqCreateRoom(): Name -->" << Name << PtH::Endl();
	pBaseEntityCall->ReqCreateRoom(Name);
}

void KBEngine::PtAccount::SelectRoomGame(uint64 RoomId)
{
	PtH::Debug() << "PtAccount::SelectRoomGame(): RoomId -->" << RoomId << PtH::Endl();
	pBaseEntityCall->SelectRoomGame(RoomId);
}

void KBEngine::PtAccount::RegisterClientReqEvent()
{
	//注册事件, 这些事件是用于在PtRoleGameMode通过KBENGINE_EVENT_FIRE宏触发事件时可以调用到这里注册的函数
	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqCreateRole", "ReqCreateRole", [this](const UKBEventData* EventData) {
		const UKBEventData_ReqCreateRole* ServerData = Cast<UKBEventData_ReqCreateRole>(EventData);
		ReqCreateRole(ServerData->RoleType, ServerData->Name);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqRemoveRole", "ReqRemoveRole", [this](const UKBEventData* EventData) {
		const UKBEventData_ReqRemoveRole* ServerData = Cast<UKBEventData_ReqRemoveRole>(EventData);
		ReqRemoveRole(ServerData->RoleInfo.Name);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("SelectRoleGame", "SelectRoleGame", [this](const UKBEventData* EventData)	{
		const UKBEventData_SelectRoleGame* ServerData = Cast<UKBEventData_SelectRoleGame>(EventData);
		SelectRoleGame(ServerData->RoleInfo.Dbid);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqRoomList", "ReqRoomList", [this](const UKBEventData* EventData) {
		ReqRoomList();
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("ReqCreateRoom", "ReqCreateRoom", [this](const UKBEventData* EventData) {
		const UKBEventData_ReqCreateRoom* ServerData = Cast<UKBEventData_ReqCreateRoom>(EventData);
		ReqCreateRoom(ServerData->RoomName);
	});

	KBENGINE_REGISTER_EVENT_OVERRIDE_FUNC("SelectRoomGame", "SelectRoomGame", [this](const UKBEventData* EventData) {
		const UKBEventData_SelectRoomGame* ServerData = Cast<UKBEventData_SelectRoomGame>(EventData);
		SelectRoomGame(ServerData->RoomId);
	});
}

