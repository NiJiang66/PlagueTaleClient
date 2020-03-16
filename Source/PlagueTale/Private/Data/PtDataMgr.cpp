// Fill out your copyright notice in the Description page of Project Settings.
#include "PtDataMgr.h"
#include "PtDataAsset.h"
#include "PtGoodDrag.h"

void FGoodInfo::InitInfo(uint8 InBlockId, uint8 InGoodId, uint8 InNumber)
{
	BlockId = InBlockId;
	GoodId = InGoodId;
	Number = InNumber;
	GoodType = UPtDataMgr::Get()->GetTypeByGoodId(GoodId);
	GoodKind = UPtDataMgr::Get()->GetKindByGoodId(GoodId);
}


UPtDataMgr* UPtDataMgr::MgrInst = nullptr;

UPtDataMgr* UPtDataMgr::Get()
{
	if (MgrInst == nullptr) {
		MgrInst = NewObject<UPtDataMgr>();
		MgrInst->AddToRoot();
		//加载资源
		MgrInst->LoadTotalData();
	}
	return MgrInst;
}

void UPtDataMgr::LoadTotalData()
{
	TotalData = LoadObject<UPtDataAsset>(NULL, TEXT("PtDataAsset'/Game/Blueprint/Data/TotalData.TotalData'"));

	GoodDatas.Empty();
	GoodDatas.Add(0, FGoodData(EGoodType::Skill, 0));
	GoodDatas.Add(1, FGoodData(EGoodType::Skill, 1));
	GoodDatas.Add(2, FGoodData(EGoodType::Skill, 2));
	GoodDatas.Add(3, FGoodData(EGoodType::Skill, 3));
	GoodDatas.Add(4, FGoodData(EGoodType::Buff, 0));
	GoodDatas.Add(5, FGoodData(EGoodType::Buff, 1));
	GoodDatas.Add(6, FGoodData(EGoodType::Buff, 2));
	GoodDatas.Add(7, FGoodData(EGoodType::Equip, 0));
	GoodDatas.Add(8, FGoodData(EGoodType::Equip, 1));
	GoodDatas.Add(9, FGoodData(EGoodType::Equip, 2));
}

UTexture* UPtDataMgr::GetGoodTexture(int32 InIndex)
{
	if (TotalData->GoodTextures.IsValidIndex(InIndex)) {
		return TotalData->GoodTextures[InIndex];
	}
	return nullptr;
}

uint8 UPtDataMgr::GetKindByGoodId(uint8 GoodId)
{
	return GoodDatas.Find(GoodId)->GoodKind;
}

EGoodType UPtDataMgr::GetTypeByGoodId(uint8 GoodId)
{
	return GoodDatas.Find(GoodId)->GoodType;
}

bool UPtDataMgr::IsGoodExit(EBagType BagType, uint8 BlockId) const
{
	switch (BagType)
	{
	case EBagType::MainBag:
		return MainBag.Contains(BlockId);
	case EBagType::SkillBag:
		return SkillBag.Contains(BlockId);
	case EBagType::BuffBag:
		return BuffBag.Contains(BlockId);
	case EBagType::EquipBag:
		return EquipBag.Contains(BlockId);
	}
	return false;
}

const FGoodInfo UPtDataMgr::GetGoodInfo(EBagType BagType, uint8 BlockId) const
{
	switch (BagType)
	{
	case EBagType::MainBag:
		return *MainBag.Find(BlockId);
	case EBagType::SkillBag:
		return *SkillBag.Find(BlockId);
	case EBagType::BuffBag:
		return *BuffBag.Find(BlockId);
	case EBagType::EquipBag:
		return *EquipBag.Find(BlockId);
	}
	return FGoodInfo();
}

void UPtDataMgr::ChangeGoodInfo(EBagType BagType, FGoodInfo GoodInfo)
{
	if (GoodInfo.IsEmpty()) {
		switch (BagType)
		{
		case EBagType::MainBag:
			MainBag.Remove(GoodInfo.BlockId);
			break;
		case EBagType::SkillBag:
			SkillBag.Remove(GoodInfo.BlockId);
			break;
		case EBagType::BuffBag:
			BuffBag.Remove(GoodInfo.BlockId);
			break;
		case EBagType::EquipBag:
			EquipBag.Remove(GoodInfo.BlockId);
			break;
		}
	}
	else {
		switch (BagType)
		{
		case EBagType::MainBag:
			MainBag.FindOrAdd(GoodInfo.BlockId).InitInfo(GoodInfo.BlockId, GoodInfo.GoodId, GoodInfo.Number);
			break;
		case EBagType::SkillBag:
			SkillBag.FindOrAdd(GoodInfo.BlockId).InitInfo(GoodInfo.BlockId, GoodInfo.GoodId, GoodInfo.Number);
			break;
		case EBagType::BuffBag:
			BuffBag.FindOrAdd(GoodInfo.BlockId).InitInfo(GoodInfo.BlockId, GoodInfo.GoodId, GoodInfo.Number);
			break;
		case EBagType::EquipBag:
			EquipBag.FindOrAdd(GoodInfo.BlockId).InitInfo(GoodInfo.BlockId, GoodInfo.GoodId, GoodInfo.Number);
			break;
		}
	}
	UpdateBagBlockDel.ExecuteIfBound(BagType, GoodInfo.BlockId);
}

bool UPtDataMgr::IsHandGoodExit()
{
	return GoodDrag != NULL;
}

FGoodInfo UPtDataMgr::GetHandGoodInfo() const
{
	return GetGoodInfo(HandBagType, HandBlockId);
}

void UPtDataMgr::ReviseHandGood()
{
	if (GoodDrag) {
		GoodDrag->RemoveFromParent();
	}
	GoodDrag = nullptr;
	UpdateBagBlockDel.ExecuteIfBound(HandBagType, HandBlockId);
}

void UPtDataMgr::ClearBagData()
{
	//重置资源
	MgrInst->GoodDrag = nullptr;

	MgrInst->MainBag.Empty();
	MgrInst->SkillBag.Empty();
	MgrInst->BuffBag.Empty();
	MgrInst->EquipBag.Empty();
}

