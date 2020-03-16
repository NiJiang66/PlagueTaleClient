// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PtBaseBag.h"
#include "PtMainBag.generated.h"

/**
 * 主背包界面
 */
UCLASS()
class PLAGUETALE_API UPtMainBag : public UPtBaseBag
{
	GENERATED_BODY()
public:
	/**	根据格子id更新背包格子数据 */
	virtual void UpdateBlock(uint8 BlockId) override;
};
