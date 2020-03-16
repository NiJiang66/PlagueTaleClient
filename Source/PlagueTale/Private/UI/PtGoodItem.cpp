// Fill out your copyright notice in the Description page of Project Settings.


#include "PtGoodItem.h"
#include "PtDataMgr.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"

void UPtGoodItem::IsAllowDragUp(bool& IsAllow)
{
	//如果已经有物品在手上
	if (UPtDataMgr::Get()->IsHandGoodExit()) {
		IsAllow = false;
		return;
	}
	IsAllow = true;
}

void UPtGoodItem::AcceptDragUp(uint8& GoodId, uint8& Number)
{
	//获取GoodInfo
	const FGoodInfo GoodInfo = UPtDataMgr::Get()->GetGoodInfo(BagType, BlockId);

	//提交物品信息给拖拽中(手中)
	UPtDataMgr::Get()->HandBagType = BagType;
	UPtDataMgr::Get()->HandBlockId = BlockId;

	//告诉GoodDrag物品信息
	GoodId = GoodInfo.GoodId;
	Number = GoodInfo.Number;
}

void UPtGoodItem::InitGoodItem(EBagType InType, uint8 InId)
{
	BagType = InType;
	BlockId = InId;
	//获取GoodInfo
	const FGoodInfo GoodInfo = UPtDataMgr::Get()->GetGoodInfo(BagType, BlockId);
	
	if (GoodInfo.Number == 1) {
		NumberText->SetText(FText());
	}
	else {
		NumberText->SetText(FText::FromString(FString::FromInt(GoodInfo.Number)));
	}
	GoodImage->SetBrushFromTexture((UTexture2D*)UPtDataMgr::Get()->GetGoodTexture(GoodInfo.GoodId));
}

void UPtGoodItem::LeaveBagBlock()
{
	//设置所在BagBlock的GoodItem为空
	LeaveBagBlockDel.ExecuteIfBound();
	//从界面移除
	RemoveFromParent();
}
