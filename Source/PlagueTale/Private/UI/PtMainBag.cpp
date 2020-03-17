// Fill out your copyright notice in the Description page of Project Settings.


#include "PtMainBag.h"
#include "PtDataMgr.h"

void UPtMainBag::UpdateBlock(uint8 BlockId)
{
	Super::UpdateBlock(BlockId);

	//根据物品信息是否存在和格子Id来设定
	if (UPtDataMgr::Get()->IsGoodExit(EBagType::MainBag, BlockId)) {

	}
	else {

	}
}
