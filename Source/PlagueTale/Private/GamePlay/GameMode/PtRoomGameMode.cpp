// Fill out your copyright notice in the Description page of Project Settings.


#include "PtRoomGameMode.h"
#include "Engine/KBEngine.h"
#include "Scripts/PtEventData.h"
#include "Scripts/PtCommon.h"
#include "PtRoomHUD.h"
#include "Kismet/GameplayStatics.h"
#include "PtRoomWidget.h"

void APtRoomGameMode::InstallEvents()
{
	Super::InstallEvents();

	KBENGINE_REGISTER_EVENT("OnReqRoomList", OnReqRoomList);
	KBENGINE_REGISTER_EVENT("OnCreateRoom", OnCreateRoom);

	// 这个事件触发时我们需要切换地图到游戏世界地图
	KBENGINE_REGISTER_EVENT("addSpaceGeometryMapping", AddSpaceGeometryMapping);
}

void APtRoomGameMode::AddSpaceGeometryMapping(const UKBEventData* EventData)
{
	const UKBEventData_addSpaceGeometryMapping* ServerData = Cast<UKBEventData_addSpaceGeometryMapping>(EventData);
	// 切割"spaces/MapName"
	FString MapName;
	ServerData->spaceResPath.Split("/", nullptr, &MapName);
	UGameplayStatics::OpenLevel(GetWorld(), FName(*MapName));
}

void APtRoomGameMode::OnReqRoomList(const UKBEventData* EventData)
{
	const UKBEventData_OnReqRoomList* ServerData = Cast<UKBEventData_OnReqRoomList>(EventData);
	//告诉房间界面生成房间列表
	APtRoomHUD* RoleHUD = Cast<APtRoomHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->MyHUD);
	if (ServerData&&RoleHUD) {
		RoleHUD->RoomWidget->OnReqRoomList(ServerData->RoomList);
	}
}

void APtRoomGameMode::OnCreateRoom(const UKBEventData* EventData)
{
	const UKBEventData_OnCreateRoom* ServerData = Cast<UKBEventData_OnCreateRoom>(EventData);
	//告诉房间界面创建房间
	APtRoomHUD* RoleHUD = Cast<APtRoomHUD>(UGameplayStatics::GetPlayerController(GetWorld(), 0)->MyHUD);
	if (ServerData&&RoleHUD) {
		RoleHUD->RoomWidget->OnCreateRoom(ServerData->RoomInfo);
	}
}
