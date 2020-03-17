// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PtBaseBag.h"
#include "PtEquipBag.generated.h"

/**
 * 装备背包Widget
 */
UCLASS()
class PLAGUETALE_API UPtEquipBag : public UPtBaseBag
{
	GENERATED_BODY()
public:
	/**	根据格子id更新背包格子数据 */
	virtual void UpdateBlock(uint8 BlockId) override;

	void SetBaseHP(int32 InBaseHP);

	void SetDefense(int32 InDefense);

	void SetPowerRatio(float InPowerRatio);

	void SetSpeedRatio(float InSpeedRatio);

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeHPText(const FText& InText);

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeDefenseText(const FText& InText);

	UFUNCTION(BlueprintImplementableEvent)
	void ChangePowerText(const FText& InText);

	UFUNCTION(BlueprintImplementableEvent)
	void ChangeSpeedText(const FText& InText);
};
