// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "PtDataAsset.generated.h"

class UTexture;

/**
 * 数据资产类
 */
UCLASS()
class PLAGUETALE_API UPtDataAsset : public UDataAsset
{
	GENERATED_BODY()

public:
	/**	保存物品图片 */
	UPROPERTY(EditAnywhere)
	TArray<UTexture*> GoodTextures;
};
