﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "PtSkillBag.h"
#include "PtDataMgr.h"

void UPtSkillBag::UpdateBlock(uint8 BlockId)
{
	Super::UpdateBlock(BlockId);

	//根据物品信息是否存在和格子Id来设定
	if (UPtDataMgr::Get()->IsGoodExit(EBagType::SkillBag, BlockId)) {

	}
	else {

	}
}
