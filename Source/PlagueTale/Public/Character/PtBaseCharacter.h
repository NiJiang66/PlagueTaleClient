// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PtBaseCharacter.generated.h"


class APtGameMode;
class UAnimMontage;
class UAnimInstance;

/**
 *	角色实体基类
 */
UCLASS()
class PLAGUETALE_API APtBaseCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	APtBaseCharacter();

	virtual void Destroyed() override;

	/**	设置目标位置，用于服务端同步客户端远程角色位置，在APtGameMode::SetPosition回调函数里调用 */
	void SetTargetPosition(FVector InPos);

	/**	设置目标旋转，用于服务端同步客户端远程角色旋转，在APtGameMode::SetDirection回调函数里调用 */
	void SetTargetRotator(FRotator InRot);

	/**	设置目标运动动画，用于服务端同步客户端远程角色运动动画 */
	void SetTargetAnim(float Speed, float Direction);

	virtual void SetBaseHP(int32 InBaseHP) {}
	virtual void SetHP(int32 InHP) {}


protected:
	virtual void BeginPlay() override;

public:
	/**	保存实体id */
	int32 EntityId;

	/**	角色类型 */
	uint8 RoleType;

	/**	角色名字 */
	FString RoleName;

	/**	保存主游戏模式 */
	APtGameMode* MainGameMode;

	/**	是不是玩家 */
	bool IsPlayer;

	/**	用于动画蓝图的速度 */
	UPROPERTY(BlueprintReadOnly)
	float Speed_Anim;
	/**	用于动画蓝图的方向 */
	UPROPERTY(BlueprintReadOnly)
	float Direction_Anim;
	/**	用于动画蓝图的是否在空中 */
	UPROPERTY(BlueprintReadOnly)
	bool IsInAir_Anim;

	/**	保存当前HP */
	UPROPERTY(BlueprintReadOnly)
	int32 HP;
	/**	基础HP */
	int32 BaseHP;

	/**	保存攻击动画蒙太奇 */
	UPROPERTY(EditAnywhere)
	UAnimMontage* AttackMontage;
	/**	保存受伤动画蒙太奇 */
	UPROPERTY(EditAnywhere)
	UAnimMontage* HurtMontage;

protected:
	/**	保存目标位置 */
	FVector TargetPosition;
	/**	保存目标旋转 */
	FRotator TargetRotator;

	/**	保存上一次更新位置的时间，用于做插值 */
	float LastUpdatePositionTime;
	/**	保存移动速度 */
	float MoveSpeed;

	/**	保存上一次同步动画的时间，用于做插值 */
	float LastUpdateAnimTime;
	/**	更新动作时间间隔 */
	float UpdateAnimSpaceTime;
	/**	剩余动作更新时间 */
	float RemainAnimSpaceTime;

	/**	目标移动速度 */
	float TargetSpeed;
	/**	目标移动角度 */
	float TargetDirection;

	/**	保存上一次的移动速度，用于做插值 */
	float LastSpeed;
	/**	保存上一次的移动角度，用于做插值 */
	float LastDirection;

	/**	保存动作蓝图 */
	UAnimInstance* CharacterAnim;

};
