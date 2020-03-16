// Fill out your copyright notice in the Description page of Project Settings.


#include "PtGoodDrag.h"
#include "Image.h"
#include "TextBlock.h"
#include "PtDataMgr.h"



void UPtGoodDrag::InitGoodInfo(uint8 GoodId, uint8 Number)
{
	//UI显示
	GoodImage->SetBrushFromTexture((UTexture2D*)UPtDataMgr::Get()->GetGoodTexture(GoodId));
	if (Number == 1) {
		NumberText->SetText(FText());
	}
	else {
		NumberText->SetText(FText::FromString(FString::FromInt(Number)));
	}
	//把自己保存到DataMgr的GoodDrag, 当前一定为空
	UPtDataMgr::Get()->GoodDrag = this;
}
