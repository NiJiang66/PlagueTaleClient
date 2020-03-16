// Fill out your copyright notice in the Description page of Project Settings.


#include "PtBaseBag.h"
#include "PtBagBlock.h"

void UPtBaseBag::UpdateBlock(uint8 BlockId)
{
	BlockGroup[BlockId]->UpdateBlock();
}
