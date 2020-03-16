// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PtActorEntity.generated.h"



/**
 *	ActorEntity基类，用于物品、技能、buff等
 */
UCLASS()
class PLAGUETALE_API APtActorEntity : public AActor
{
	GENERATED_BODY()
	
public:	
	APtActorEntity();

	/**	设置目标位置 */
	void SetTargetPosition(FVector InPos);

	virtual void Tick(float DeltaTime) override;

protected:
	virtual void BeginPlay() override;

public:
	/**	唯一的EntityId */
	int32 EntityId;

	class APtGameMode* MainGameMode;

protected:

	/**	将要移动到的目标位置 */
	FVector TargetPosition;

	/**	上一次更新位置的时间 */
	float LastUpdatePositionTime;

	/**	移动速度 */
	float MoveSpeed;
};
