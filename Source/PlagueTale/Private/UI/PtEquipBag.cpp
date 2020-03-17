// Fill out your copyright notice in the Description page of Project Settings.


#include "PtEquipBag.h"
#include "PtDataMgr.h"

void UPtEquipBag::UpdateBlock(uint8 BlockId)
{
	Super::UpdateBlock(BlockId);

	//根据物品信息是否存在和格子Id来设定
	if (UPtDataMgr::Get()->IsGoodExit(EBagType::EquipBag, BlockId)) {

	}
	else {
		
	}
}

void UPtEquipBag::SetBaseHP(int32 InBaseHP)
{
	ChangeHPText(FText::FromString(FString::FromInt(InBaseHP)));
}

void UPtEquipBag::SetDefense(int32 InDefense)
{
	ChangeDefenseText(FText::FromString(FString::FromInt(InDefense)));
}

void UPtEquipBag::SetPowerRatio(float InPowerRatio)
{
	FString PowerInfo = FString::FromInt(FMath::FloorToInt(InPowerRatio * 100)).Append("%");
	ChangePowerText(FText::FromString(PowerInfo));
}

void UPtEquipBag::SetSpeedRatio(float InSpeedRatio)
{
	FString SpeedInfo = FString::FromInt(FMath::FloorToInt(InSpeedRatio * 100)).Append("%");
	ChangeSpeedText(FText::FromString(SpeedInfo));
}
