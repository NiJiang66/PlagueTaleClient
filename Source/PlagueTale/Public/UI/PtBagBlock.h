// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PtDataMgr.h"
#include "PtBagBlock.generated.h"



class UOverlay;
class UPtGoodItem;

/**
 * 背包格子Widget
 */
UCLASS()
class PLAGUETALE_API UPtBagBlock : public UUserWidget
{
	GENERATED_BODY()
public:

	/**	初始化格子类型与Id */
	UFUNCTION(BlueprintCallable)
	void InitBlockInfo(EBagType InType, uint8 InId);

	/**	是否允许被放入物品 */
	UFUNCTION(BlueprintCallable, BlueprintPure)
	void IsAllowDropDown(bool& DropResult);

	/**	向服务器请求转移物品, 同时创建出一个新的GoodItem添加到格子 */
	UFUNCTION(BlueprintCallable)
	void RequestPassGood();

	/**	把物品放回原格子 */
	UFUNCTION(BlueprintCallable)
	void ReviseDragGood();

	/**	让BagBlock根据数据自己更新 */
	void UpdateBlock();

public:
	/**	RootBox */
	UPROPERTY(Meta = (BindWidget))
	UOverlay* RootBox;

	/**	背包类型 */
	UPROPERTY(BlueprintReadOnly)
	EBagType BagType;

	/**	格子id */
	UPROPERTY(BlueprintReadOnly)
	uint8 BlockId;

	/**	物品Item的UserWidget类型 */
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	TSubclassOf<UPtGoodItem> GoodItemClass;

	/**	保存物品Item的UserWidget */
	UPROPERTY(BlueprintReadWrite)
	UPtGoodItem* GoodItem;
};
