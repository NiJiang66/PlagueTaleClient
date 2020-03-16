// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PtGoodDrag.generated.h"

class UImage;
class UTextBlock;

/**
 * 拖拽物品Widget
 */
UCLASS()
class PLAGUETALE_API UPtGoodDrag : public UUserWidget
{
	GENERATED_BODY()
public:
	/**	初始化 */
	UFUNCTION(BlueprintCallable)
	void InitGoodInfo(uint8 GoodId, uint8 Number);

public:
	/**	保存物品图片 */
	UPROPERTY(Meta = (BindWidget))
	UImage* GoodImage;

	/**	保存数量文字 */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* NumberText;
};
