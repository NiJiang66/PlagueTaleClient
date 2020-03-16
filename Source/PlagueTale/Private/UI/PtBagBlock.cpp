// Fill out your copyright notice in the Description page of Project Settings.


#include "PtBagBlock.h"
#include "PtDataMgr.h"
#include "Scripts/PtEventData.h"
#include "PtGoodItem.h"
#include "Engine/KBEvent.h"
#include "Components/Overlay.h"
#include "Components/OverlaySlot.h"

void UPtBagBlock::InitBlockInfo(EBagType InType, uint8 InId)
{
	BagType = InType;
	BlockId = InId;
}

void UPtBagBlock::IsAllowDropDown(bool& DropResult)
{
	//提前设置IsAllow为false
	DropResult = false;

	//判断框里是否有物品, 有物品直接返回
	if (GoodItem) { return; }		

	//是否是原来的格子
	if (UPtDataMgr::Get()->HandBagType == BagType && UPtDataMgr::Get()->HandBlockId == BlockId)
		return;

	//获取拖拽中的物品信息
	const FGoodInfo HandGoodInfo = UPtDataMgr::Get()->GetHandGoodInfo();

	//判断是否匹配
	switch (BagType)
	{
	case EBagType::MainBag:
		//主背包什么都可放置
		DropResult = true;
		break;
	case EBagType::SkillBag:
		if (HandGoodInfo.GoodType == EGoodType::Skill) {
			DropResult = true;
		}			
		break;
	case EBagType::BuffBag:
		if (HandGoodInfo.GoodType == EGoodType::Buff) {
			DropResult = true;
		}
		break;
	case EBagType::EquipBag:
		if (HandGoodInfo.GoodType == EGoodType::Equip) {
			//装备还需要判断表格id和装备种类Id是否相同
			if (HandGoodInfo.GoodKind == BlockId) {
				DropResult = true;
			}
		}
		break;
	}
}

void UPtBagBlock::RequestPassGood()
{
	//向服务器发送移动物品请求, 回调到达之后会矫正数据
	UKBEventData_PassGood* EventData = NewObject<UKBEventData_PassGood>();
	EventData->ArcBagType = (uint8)UPtDataMgr::Get()->HandBagType;
	EventData->ArcBlockId = UPtDataMgr::Get()->HandBlockId;
	EventData->DesBagType = (uint8)BagType;
	EventData->DesBlockId = BlockId;
	KBENGINE_EVENT_FIRE("PassGood", EventData);

	//清空手持物品信息, 只是设置GoodDrag为nullptr, 让其被自动回收
	UPtDataMgr::Get()->GoodDrag = nullptr;

	//创建空的物品信息, 空格子数据
	FGoodInfo ArcGoodInfo;
	ArcGoodInfo.InitInfo(UPtDataMgr::Get()->HandBlockId, 0, 0);

	//当前格子更新的物品信息
	FGoodInfo DesGoodInfo = UPtDataMgr::Get()->GetHandGoodInfo();
	//修改BlockId
	DesGoodInfo.BlockId = BlockId;

	//交换两个格子的数据
	UPtDataMgr::Get()->ChangeGoodInfo((EBagType)UPtDataMgr::Get()->HandBagType, ArcGoodInfo);
	UPtDataMgr::Get()->ChangeGoodInfo(BagType, DesGoodInfo);
}

void UPtBagBlock::ReviseDragGood()
{
	UPtDataMgr::Get()->ReviseHandGood();
}

void UPtBagBlock::UpdateBlock()
{
	//如果数据中心不存在该表格的物品
	if (UPtDataMgr::Get()->IsGoodExit(BagType, BlockId) == false) {
		//如果GoodItem存在, 进行销毁
		if (GoodItem) {
			GoodItem->RemoveFromParent();
			GoodItem = nullptr;
		}
	}
	else {
		const FGoodInfo GoodInfo = UPtDataMgr::Get()->GetGoodInfo(BagType, BlockId);
		//判断有没有GoodItem, 没有的话就生成
		if (!GoodItem)
		{
			GoodItem = CreateWidget<UPtGoodItem>(this, GoodItemClass);
			UOverlaySlot* ItemSlot = RootBox->AddChildToOverlay(GoodItem);
			ItemSlot->SetHorizontalAlignment(HAlign_Fill);
			ItemSlot->SetVerticalAlignment(VAlign_Fill);

			//绑定委托
			GoodItem->LeaveBagBlockDel.BindLambda([this]() {
				GoodItem = nullptr;
			});
		}
		//添加数据给GoodItem
		GoodItem->InitGoodItem(BagType, BlockId);
	}
}
