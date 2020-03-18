// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PTBaseCharacter.h"
#include "PtPlayerCharacter.generated.h"

class APtPlayerController;
class UCameraComponent;
class USpringArmComponent;
class UPtMainGameWidget;

/**
 * 游戏场景的玩家角色
 */
UCLASS()
class PLAGUETALE_API APtPlayerCharacter : public APtBaseCharacter
{
	GENERATED_BODY()
		
public:
	APtPlayerCharacter();

	virtual void Tick(float DeltaSeconds) override;

	/**	设置输入组件，当被Controller Possess时的回调 */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/**	设置基础血量 */
	virtual void SetBaseHP(int32 InBaseHP) override;
	/**	设置当前血量 */
	virtual void SetHP(int32 InHP) override;
	/**	设置速度 */
	virtual void SetSpeedRatio(float InSpeedRatio) override;

	/**	攻击，包括技能，SkillId为 0:普通攻击  1：技能1  2技能2  3：技能3  4：技能4 */
	void Attack(uint8 SkillId);

	/**	攻击回调，实现具体的攻击表现 */
	virtual void OnAttack(uint8 SkillID)override;

protected:
	void DoJump();
	void DoStopJump();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void AnimUpdate();

	/**	操作背包 */
	void OperateBag();
	/**	开始在聊天框输入 */
	void StartWriteMessage();

	/**	请求普通攻击 */
	void RequestNormalAttack();

	/**	四个技能的触发事件 */
	void SkillOne();
	void SkillTwo();
	void SkillThree();
	void SkillFour();

	/**	请求使用技能 */
	void RequestSkill(uint8 BlockId);

	/**	三个Buff的触发事件 */
	void BuffOne();
	void BuffTwo();
	void BuffThree();
	/**	请求使用BUff */
	void RequestBuff(uint8 BlockId);

protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;
public:
	/**	游戏场景玩家控制器 */
	APtPlayerController* MainController;

	/**	游戏主界面 */
	UPROPERTY()
	UPtMainGameWidget* MainGameWidget;

	UPROPERTY(EditAnywhere)
	float TurnRate;
	UPROPERTY(EditAnywhere)
	float LookUpRate;

protected:
	UPROPERTY(EditAnywhere)
	UCameraComponent* FollowCamera = nullptr;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraBoom;

	UPROPERTY(EditAnywhere)
	USceneComponent* SkillPoint;

	/**	更新动画到服务端定时器句柄 */
	FTimerHandle AnimUpdateHandle;

	/**	是否显示背包 */
	UPROPERTY()
	bool IsShowBag;

};
