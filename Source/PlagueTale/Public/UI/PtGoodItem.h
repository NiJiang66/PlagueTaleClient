// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PtDataMgr.h"
#include "PtGoodItem.generated.h"


class UImage;
class UTextBlock;

//从BagBlock移出的委托
DECLARE_DELEGATE(FLeaveBagBlock)

/**
 * 物品Item Widget
 */
UCLASS()
class PLAGUETALE_API UPtGoodItem : public UUserWidget
{
	GENERATED_BODY()
public:
	/**	是否允许放入 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	void IsAllowDragUp(bool& IsAllow);

	/**	接受移出 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	void AcceptDragUp(uint8& GoodId, uint8& Number);

	/**	初始化 */
	UFUNCTION(BlueprintCallable)
	void InitGoodItem(EBagType InType, uint8 InId);

	/**	移出格子 */
	UFUNCTION(BlueprintCallable)
	void LeaveBagBlock();

public:
	/**	保存物品图片 */
	UPROPERTY(Meta = (BindWidget))
	UImage* GoodImage;

	/**	数量文本 */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* NumberText;

	/**	只保存BagType和BlockId, 不保存实际物品数据 */
	EBagType BagType;
	uint8 BlockId;

	/**	从BagBlock移出的委托 */
	FLeaveBagBlock LeaveBagBlockDel;
};
