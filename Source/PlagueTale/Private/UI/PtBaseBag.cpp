// Fill out your copyright notice in the Description page of Project Settings.


#include "PtBaseBag.h"
#include "PtBagBlock.h"
#include "Scripts/PtCommon.h"

void UPtBaseBag::UpdateBlock(uint8 BlockId)
{
	TArray<UPtBagBlock*> Tmp;
	for (int i = 0; i < BlockGroup.Num(); ++i) {
		if (BlockGroup.IsValidIndex(i) && BlockGroup[i]) {
			Tmp.Add(BlockGroup[i]);
		}
	}
	BlockGroup.Emplace();
	BlockGroup = Tmp;
	if (BlockGroup.IsValidIndex(BlockId) && BlockGroup[BlockId]) {
		BlockGroup[BlockId]->UpdateBlock();
		//PtH::Debug() << "UPtBaseBag::UpdateBlock!!!!!!!!``````" << PtH::Endl();
	}
}
