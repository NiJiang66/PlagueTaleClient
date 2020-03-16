// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PtBaseBag.generated.h"


class UPtBagBlock;

/**
 * 背包Widget基类
 */
UCLASS()
class PLAGUETALE_API UPtBaseBag : public UUserWidget
{
	GENERATED_BODY()
public:
	/**	根据格子id更新背包格子数据 */
	virtual void UpdateBlock(uint8 BlockId);

public:
	/**	保存背包里的所有格子Widget */
	UPROPERTY(BlueprintReadWrite)
	TArray<UPtBagBlock*> BlockGroup;
};
