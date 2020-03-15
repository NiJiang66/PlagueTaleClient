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

/**	请求角色列表回调的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqRoleList : public UKBEventData 
{
	GENERATED_BODY()
public:
	UPROPERTY()
	TArray<FROLE_INFO> RoleList;
};

/**	请求创建角色回调的事件数据类 */
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

/**	请求删除角色回调的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnRemoveRole : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FROLE_INFO RoleInfo;
};

/**	请求选择角色进行游戏回调的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnSelectRoleGame : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	uint64 Dbid;
};

/**	客户端请求服务端创建角色的事件数据类 */
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

/**	客户端请求服务端删除角色的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqRemoveRole : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FROLE_INFO RoleInfo;
};

/**	客户端请求服务端选择角色进行游戏的事件数据类 */
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


/**	客户端请求服务端创建房间的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReqCreateRoom : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	FString RoomName;
};

/**	客户端请求服务端选择房间进行游戏的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SelectRoomGame : public UKBEventData
{
	GENERATED_BODY()
public:
	UPROPERTY()
	uint64 RoomId;
};

/**	请求房间列表回调的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqRoomList : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	房间信息数组 */
	UPROPERTY()
	TArray<FROOM_INFO> RoomList;
};

/**	请求创建房间回调的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnCreateRoom : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	房间信息数组 */
	UPROPERTY()
	FROOM_INFO RoomInfo;
};


/**	请求更新动画回调的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnAnimUpdate : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	实体Id */
	UPROPERTY()
	int32 EntityId;
	/**	速度 */
	UPROPERTY()
	float Speed;
	/**	方向 */
	UPROPERTY()
	float Direction;
};

/**	客户端请求服务端更新动画的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_AnimUpdate : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	速度 */
	UPROPERTY()
	float Speed;
	/**	方向 */
	UPROPERTY()
	float Direction;
};

/**	客户端请求服务端设置基础血量的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SetBaseHP : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	实体Id */
	UPROPERTY()
	int32 EntityId;
	/**	是否是玩家 */
	UPROPERTY()
	bool IsPlayer;
	/**	基础血量 */
	UPROPERTY()
	int32 BaseHP;
};

/**	客户端请求服务端设置当前血量的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SetHP : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	实体Id */
	UPROPERTY()
	int32 EntityId;
	/**	是否是玩家 */
	UPROPERTY()
	bool IsPlayer;
	/**	当前血量 */
	UPROPERTY()
	int32 HP;
};

/**	客户端攻击的回调的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnAttack : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	角色实体id */
	UPROPERTY()
	int32 EntityId;
};



/**
 * 实现各种注册事件参数类的地方，对应服务器定义的数据结构
 */
UCLASS()
class KBENGINEPLUGINS_API UPtEventData : public UObject
{
	GENERATED_BODY()
	
};
