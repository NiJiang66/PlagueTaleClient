// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PTBaseCharacter.h"
#include "PtEnemyCharacter.generated.h"

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
};
