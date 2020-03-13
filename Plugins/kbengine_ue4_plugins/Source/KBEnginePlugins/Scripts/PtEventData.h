// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/KBEvent.h"
#include "UObject/NoExportTypes.h"
#include "PtEventData.generated.h"

/**	角色信息结构体 */
USTRUCT()
struct FROLE_INFO
{
	GENERATED_BODY()

	UPROPERTY()
	uint64 Dbid;
	UPROPERTY()
	FString Name;
	UPROPERTY()
	uint8 RoleType;
	UPROPERTY()
	bool IsLastRole;

	void InitData(DBID InDbid, const FString& InName, uint8 InRolrType, bool InIsLastRole) {
		Dbid = InDbid;
		Name = InName;
		RoleType = InRolrType;
		IsLastRole = InIsLastRole;
	}
};

/**	请求角色列表回调事件的数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqRoleList : public UKBEventData 
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<FROLE_INFO> RoleList;
};

/**	请求创建角色回调事件的数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnCreateRoleResult : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	uint8 ErrorCode;
	UPROPERTY()
	FString ErrorStr;
	UPROPERTY()
	FROLE_INFO RoleInfo;
};

/**	请求删除角色回调事件的数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnRemoveRole : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FROLE_INFO RoleInfo;
};

/**	请求选择角色进行游戏回调事件的数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnSelectRoleGame : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	uint64 Dbid;
};

/**	客户端请求创建角色事件的数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqCreateRole : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	uint8 RoleType;
	UPROPERTY()
	FString Name;
};

/**	客户端请求删除角色事件的数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqRemoveRole : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FROLE_INFO RoleInfo;
};

/**	客户端请求选择角色进行游戏事件的数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SelectRoleGame : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FROLE_INFO RoleInfo;
};



/**	房间信息数据结构 */
USTRUCT()
struct FROOM_INFO 
{
	GENERATED_BODY()

	UPROPERTY()
	uint64 RoomId;
	UPROPERTY()
	FString Name;

	void InitData(uint64 InRoomId, const FString& InName) {
		RoomId = InRoomId;
		Name = InName;
	}
};


/**	客户端请求创建房间事件的数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqCreateRoom : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString RoomName;
};

/**	客户端请求选择房间进行游戏事件的数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SelectRoomGame : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	uint64 RoomId;
};

/**	客户端请求房间列表事件的数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqRoomList : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	房间信息数组 */
	UPROPERTY()
	TArray<FROOM_INFO> RoomList;
};

/**	客户端请求创建房间事件的数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnCreateRoom : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	房间信息数组 */
	UPROPERTY()
		FROOM_INFO RoomInfo;
};



/**
 * 实现各种注册事件参数类的地方，对应服务器定义的数据结构
 */
UCLASS()
class KBENGINEPLUGINS_API UPtEventData : public UObject
{
	GENERATED_BODY()
	
};
