// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GamePlay/GameMode/PTGameModeBase.h"
#include "PtGameMode.generated.h"

class APtPlayerCharacter;
class APtRemotePlayerCharacter;
class APtBaseCharacter;
class APtEnemyCharacter;

/**
 * 主游戏场景的游戏模式
 */
UCLASS()
class PLAGUETALE_API APtGameMode : public APtGameModeBase
{
	GENERATED_BODY()
public:
	APtGameMode();

	/**	安装进入场景时需要监听的KBE事件 */
	virtual void InstallEvents();
	/**	注销进入场景时注册的KBE事件 */
	virtual void UnInstallEvents();


protected:
	virtual void BeginPlay() override;

protected:

	void OnEnterWorld(const UKBEventData* EventData);

	void OnLeaveWorld(const UKBEventData* EventData);

	void OnEnterSpace(const UKBEventData* EventData);

	void OnLeaveSpace(const UKBEventData* EventData);
	/**	设置非本地角色位置 */
	void SetPosition(const UKBEventData* EventData);
	/**	设置非本地角色旋转 */
	void SetDirection(const UKBEventData* EventData);

	void UpdatePosition(const UKBEventData* EventData);


	void OnAnimUpdate(const UKBEventData* EventData);

	void SetBaseHP(const UKBEventData* EventData);

	void SetHP(const UKBEventData* EventData);

public:

	/**	玩家角色类型列表 */
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APtPlayerCharacter>> PlayerClassList;
	/**	保存玩家角色 */
	UPROPERTY()
	APtPlayerCharacter* PlayerCharacter;

	/**	远程玩家角色类型列表 */
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APtRemotePlayerCharacter>> RemotePlayerClassList;
	/**	怪物类型列表 */
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<APtEnemyCharacter>> MonsterClassList;
	/**	实体ID对应角色指针，保存所有远程玩家与怪物*/
	UPROPERTY()
	TMap<int32, APtBaseCharacter*> OtherCharacters;



	/** 保存主游戏关卡界面 */
	class UPtMainGameWidget* RoleWidget;
};
