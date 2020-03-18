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

/**	物品信息结构体 */
USTRUCT()
struct FGOOD_INFO
{
	GENERATED_BODY()
public:
	/**	格子id */
	UPROPERTY()
	uint8 BlockId;
	/**	物品id */
	UPROPERTY()
	uint8 GoodId;
	/**	数量 */
	UPROPERTY()
	uint8 Number;

	void InitInfo(uint8 InBlockId, uint8 InGoodId, uint8 InNumber) {
		BlockId = InBlockId;
		GoodId = InGoodId;
		Number = InNumber;
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

/**	客户端请求服务端设置防御力的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SetDefense : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	实体Id */
	UPROPERTY()
	int32 EntityId;
	/**	防御力 */
	UPROPERTY()
	int32 Defense;	
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

/**	客户端请求服务端设置当前力量加成的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SetPowerRatio : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	实体Id */
	UPROPERTY()
	int32 EntityId;
	/**	力量加成 */
	UPROPERTY()
	float PowerRatio;
}; 

/**	客户端请求服务端设置当前速度加成的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_SetSpeedRatio : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	实体Id */
	UPROPERTY()
	int32 EntityId;
	/**	速度加成 */
	UPROPERTY()
	float SpeedRatio;
};

/**	客户端请求服务端攻击的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_Attack : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	技能id */
	UPROPERTY()
	uint8 SkillId;
	/**	生成位置 */
	UPROPERTY()
	FVector SpawnPos;
	/**	移动目标位置 */
	UPROPERTY()
	FVector TargetPos;
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
	/**	技能id ， 0:普通攻击  1：技能1  2技能2  3：技能3  4：技能4*/
	UPROPERTY()
	int32 SkillId;
};

/**	客户端请求服务端使用物品的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_ReduceGood : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	背包类型 */
	UPROPERTY()
	uint8 BagType;
	/**	格子id */
	UPROPERTY()
	uint8 BlockId;
}; 
/**	客户端使用物品的回调的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReduceGood : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	使用结果 */
	UPROPERTY()
	uint8 ReduceRes;
	/**	背包类型 */
	UPROPERTY()
	uint8 BagType;
	/**	物品信息 */
	UPROPERTY()
	FGOOD_INFO GoodInfo;
};

/**	客户端请求服务端移动物品的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_PassGood : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	移出背包的物品类型 */
	UPROPERTY()
	uint8 ArcBagType;
	/**	移出背包的格子id */
	UPROPERTY()
	uint8 ArcBlockId;
	/**	放入背包的物品类型 */
	UPROPERTY()
	uint8 DesBagType;
	/**	放入背包的格子id */
	UPROPERTY()
	uint8 DesBlockId;
};
/**	客户端移动物品的的回调的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnPassGood : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	移出背包的类型 */
	UPROPERTY()
	uint8 ArcBagType;
	/**	移出的物品信息 */
	UPROPERTY()
	FGOOD_INFO ArcGoodInfo;
	/**	放入的背包类型 */
	UPROPERTY()
	uint8 DesBagType;
	/**	放入的物品信息 */
	UPROPERTY()
	FGOOD_INFO DesGoodInfo;
};

/**	添加物品的回调的事件数据类(添加物品的逻辑在服务端) */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnIncreaseGood : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	背包类型 */
	UPROPERTY()
	uint8 BagType;
	/**	物品信息 */
	UPROPERTY()
	FGOOD_INFO GoodInfo;
};

/**	请求背包列表的回调的事件数据类 */
UCLASS()
class KBENGINEPLUGINS_API UKBEventData_OnReqBagList : public UKBEventData
{
	GENERATED_BODY()
public:
	/**	主背包数据 */
	UPROPERTY()
	TArray<FGOOD_INFO> MainBag;
	/**	技能背包数据 */
	UPROPERTY()
	TArray<FGOOD_INFO> SkillBag;
	/**	buff背包数据 */
	UPROPERTY()
	TArray<FGOOD_INFO> BuffBag;
	/**	装备背包数据 */
	UPROPERTY()
	TArray<FGOOD_INFO> EquipBag;
};




/**
 * 实现各种注册事件参数类的地方，对应服务器定义的数据结构
 */
UCLASS()
class KBENGINEPLUGINS_API UPtEventData : public UObject
{
	GENERATED_BODY()
	
};
