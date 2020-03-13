// Fill out your copyright notice in the Description page of Project Settings.


#include "PtRoleGameMode.h"
#include "Engine/KBEngine.h"
#include "Scripts/PtEventData.h"
#include "Scripts/PtCommon.h"
#include "Scene/PtRenderActor.h"

#include "PtRoleHUD.h"
#include "PtStartController.h"
#include "EngineUtils.h"
#include "Kismet/GameplayStatics.h"
#include "PtRoleUserWidget.h"


APtRoleGameMode::APtRoleGameMode()
{
	PlayerControllerClass = APtStartController::StaticClass();
	HUDClass = APtRoleHUD::StaticClass();
}

void APtRoleGameMode::InstallEvents()
{
	Super::InstallEvents();

	KBENGINE_REGISTER_EVENT("OnReqRoleList", OnReqRoleList);
	KBENGINE_REGISTER_EVENT("OnCreateRoleResult", OnCreateRoleResult);
	KBENGINE_REGISTER_EVENT("OnRemoveRole", OnRemoveRole);
	KBENGINE_REGISTER_EVENT("OnSelectRoleGame", OnSelectRoleGame);
}

void APtRoleGameMode::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

}

void APtRoleGameMode::ReqCreateRole(uint8 RoleType, const FString& Name)
{
	//使用KBENGINE_EVENT_FIRE执行在PtAccount下绑定的函数
	UKBEventData_ReqCreateRole* EventData = NewObject<UKBEventData_ReqCreateRole>();
	EventData->RoleType = RoleType;
	EventData->Name = Name;
	KBENGINE_EVENT_FIRE("ReqCreateRole", EventData);
}

void APtRoleGameMode::ReqRemoveRole(const FROLE_INFO& RoleInfo)
{
	//使用KBENGINE_EVENT_FIRE执行在PtAccount下绑定的函数
	UKBEventData_ReqRemoveRole* EventData = NewObject<UKBEventData_ReqRemoveRole>();
	EventData->RoleInfo = RoleInfo;
	KBENGINE_EVENT_FIRE("ReqRemoveRole", EventData);
}

void APtRoleGameMode::SelectRoleGame(const FROLE_INFO& RoleInfo)
{
	//使用KBENGINE_EVENT_FIRE执行在PtAccount下绑定的函数
	UKBEventData_SelectRoleGame* EventData = NewObject<UKBEventData_SelectRoleGame>();
	EventData->RoleInfo = RoleInfo;
	KBENGINE_EVENT_FIRE("SelectRoleGame", EventData);
}

void APtRoleGameMode::BeginPlay()
{
	Super::BeginPlay();

	//获取RenderActor
	for (TActorIterator<APtRenderActor> ActorItr(GetWorld()); ActorItr; ++ActorItr)	{
		RenderActor = Cast<APtRenderActor>(*ActorItr);
	}
}

void APtRoleGameMode::OnReqRoleList(const UKBEventData* EventData)
{
	const UKBEventData_OnReqRoleList* ServerData = Cast<UKBEventData_OnReqRoleList>(EventData);
	//告诉角色界面生成角色列表
	APtRoleHUD* RoleHUD = Cast<APtRoleHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->MyHUD);
	if (ServerData&&RoleHUD) {
		RoleHUD->RoleWidget->OnReqRoleList(ServerData->RoleList);
	}
}

void APtRoleGameMode::OnCreateRoleResult(const UKBEventData* EventData)
{
	const UKBEventData_OnCreateRoleResult* ServerData = Cast<UKBEventData_OnCreateRoleResult>(EventData);
	//告诉角色界面生成角色条目
	APtRoleHUD* RoleHUD = Cast<APtRoleHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->MyHUD);
	if (ServerData && RoleHUD && ServerData->ErrorCode == 0) {
		RoleHUD->RoleWidget->OnCreateRoleResult(ServerData->RoleInfo);
	}
}

void APtRoleGameMode::OnRemoveRole(const UKBEventData* EventData)
{
	const UKBEventData_OnRemoveRole* ServerData = Cast<UKBEventData_OnRemoveRole>(EventData);
	//告诉角色界面删除角色条目
	APtRoleHUD* RoleHUD = Cast<APtRoleHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->MyHUD);
	if (ServerData&&RoleHUD) {
		RoleHUD->RoleWidget->OnRemoveRole(ServerData->RoleInfo);
	}
}

void APtRoleGameMode::OnSelectRoleGame(const UKBEventData* EventData)
{
	//const UKBEventData_OnSelectRoleGame* ServerData = Cast<UKBEventData_OnSelectRoleGame>(EventData);
	//直接跳转场景到房间选择地图
	UGameplayStatics::OpenLevel(GetWorld(), FName("RoomMap"));
}
