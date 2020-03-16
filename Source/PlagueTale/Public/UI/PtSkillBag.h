// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PtBaseBag.h"
#include "PtSkillBag.generated.h"

/**
 * 技能背包Widget
 */
UCLASS()
class PLAGUETALE_API UPtSkillBag : public UPtBaseBag
{
	GENERATED_BODY()

public:
	/**	根据格子id更新背包格子数据 */
	virtual void UpdateBlock(uint8 BlockId) override;

};
