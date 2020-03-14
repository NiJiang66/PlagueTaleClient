// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PTBaseCharacter.h"
#include "PtPlayerCharacter.generated.h"

class APtPlayerController;
class UCameraComponent;
class USpringArmComponent;

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

	virtual void SetBaseHP(int32 InBaseHP) override;

	virtual void SetHP(int32 InHP) override;


protected:
	void DoJump();
	void DoStopJump();
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Turn(float Value);
	void LookUp(float Value);

	void AnimUpdate();

protected:
	virtual void BeginPlay() override;

	virtual void Destroyed() override;
public:
	/**	游戏场景玩家控制器 */
	APtPlayerController* MainController;

	UPROPERTY(EditAnywhere)
	float TurnRate;
	UPROPERTY(EditAnywhere)
	float LookUpRate;

protected:
	UPROPERTY(EditAnywhere)
	UCameraComponent* FollowCamera = nullptr;
	UPROPERTY(EditAnywhere)
	USpringArmComponent* CameraBoom;

	//更新动画到服务端定时器句柄
	FTimerHandle AnimUpdateHandle;
};
