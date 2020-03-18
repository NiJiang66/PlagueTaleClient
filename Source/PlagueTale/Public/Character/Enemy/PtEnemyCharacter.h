// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PTBaseCharacter.h"
#include "PtEnemyCharacter.generated.h"


class UPtBloodBar;
class UWidgetComponent;

/**
 * 怪物角色类（敌人）
 */
UCLASS()
class PLAGUETALE_API APtEnemyCharacter : public APtBaseCharacter
{
	GENERATED_BODY()
public:
	APtEnemyCharacter();

	virtual void Tick(float DeltaTime) override;

	/**	设置基础血量 */
	virtual void SetBaseHP(int32 InBaseHP) override;
	/**	设置hp */
	virtual void SetHP(int32 InHP) override;

	/**	攻击回调，实现具体的攻击表现 */
	virtual void OnAttack(uint8 SkillID)override;

	/**	播放死亡动画 */
	void PlayDeath();

protected:
	virtual void BeginPlay() override;

	/**	销毁怪物 */
	void MonsterDestroy();

public:
	/**	血条UIComponent */
	UPROPERTY(EditAnywhere)
	UWidgetComponent* BloodBarComponent;

protected:
	/**	血量Var */
	UPtBloodBar* BloodBar;
	/**	计时器 */
	FTimerHandle DestroyHandle;
};
