// Fill out your copyright notice in the Description page of Project Settings.


#include "PtMainGameWidget.h"
#include "TextBlock.h"
#include "ProgressBar.h"
#include "Overlay.h"

#include "Character/Player/PtPlayerCharacter.h"
#include "Engine/KBEngine.h"
#include "Engine/KBEvent.h"
#include "Scripts/PtEventData.h"
#include "Scripts/PtCommon.h"

#include "PtSkillBag.h"
#include "PtBuffBag.h"
#include "PtEquipBag.h"
#include "PtMainBag.h"


void UPtMainGameWidget::InstallEvents(FText RoomName)
{
	//设置房间名字
	RoomText->SetText(RoomName);

	//先重置背包数据
	UPtDataMgr::Get()->ClearBagData();
	//绑定更新背包格子委托, 这样子修改数据的背包格子物品就可以直接更新UI了
	UPtDataMgr::Get()->UpdateBagBlockDel.BindUObject(this, &UPtMainGameWidget::UpdateBagBlock);

	//绑定背包远程回调方法, 注册了的对象一定要注销
	KBENGINE_REGISTER_EVENT("OnReqBagList", OnReqBagList);
	KBENGINE_REGISTER_EVENT("OnIncreaseGood", OnIncreaseGood);
	KBENGINE_REGISTER_EVENT("OnPassGood", OnPassGood);
	KBENGINE_REGISTER_EVENT("OnReduceGood", OnReduceGood);


}

void UPtMainGameWidget::UnInstallEvents()
{
	//注销该对象绑定的所有KBE事件
	KBENGINE_DEREGISTER_ALL_EVENT();
}

void UPtMainGameWidget::SetName(FString InName)
{
	NameText->SetText(FText::FromString(*InName));
}

void UPtMainGameWidget::SetHPPercent(float InPercent)
{
	BloodProgress->SetPercent(InPercent);
	//根据剩余血量比例设置颜色
	BloodProgress->SetFillColorAndOpacity(FLinearColor(1.f - InPercent, InPercent, 0.f));

	//如果血值为0, 显示复活UI
	if (InPercent == 0.f) {
		if (ReliveBox->GetVisibility() == ESlateVisibility::Hidden) {
			ReliveBox->SetVisibility(ESlateVisibility::Visible);
		}
	}
	else {
		if (ReliveBox->GetVisibility() == ESlateVisibility::Visible) {
			ReliveBox->SetVisibility(ESlateVisibility::Hidden);
		}
	}
}

void UPtMainGameWidget::SetBaseHP(int32 InBaseHP)
{
	EquipBag->SetBaseHP(InBaseHP);
}

void UPtMainGameWidget::SetDefense(int32 InDefense)
{
	EquipBag->SetDefense(InDefense);
}

void UPtMainGameWidget::SetPowerRatio(float InPowerRatio)
{
	EquipBag->SetPowerRatio(InPowerRatio);
}

void UPtMainGameWidget::SetSpeedRatio(float InSpeedRatio)
{
	EquipBag->SetSpeedRatio(InSpeedRatio);
}

void UPtMainGameWidget::OpenOrCloseBag(bool IsOpen)
{
	if (IsOpen) {
		MainBag->SetVisibility(ESlateVisibility::Visible);
		EquipBag->SetVisibility(ESlateVisibility::Visible);
	}
	else {
		MainBag->SetVisibility(ESlateVisibility::Hidden);
		EquipBag->SetVisibility(ESlateVisibility::Hidden);
	}
}

void UPtMainGameWidget::OnPlayerDead()
{
	//保存背包数据, 如果当前手上有物品
	UPtDataMgr::Get()->ReviseHandGood();
	//隐藏背包
	OpenOrCloseBag(false);

	//显示复活按钮
	ReliveBox->SetVisibility(ESlateVisibility::Visible);
}

void UPtMainGameWidget::OnPlayerRelive()
{
	//隐藏复活按钮
	ReliveBox->SetVisibility(ESlateVisibility::Hidden);
}

void UPtMainGameWidget::ReviseDragGood()
{
	UPtDataMgr::Get()->ReviseHandGood();
}

void UPtMainGameWidget::ReliveEvent()
{
	//告诉服务端复活玩家，在KBEngine::PtRole::__init__注册
	KBENGINE_EVENT_FIRE("Relive", NewObject<UKBEventData>());
}

void UPtMainGameWidget::OnReqBagList(const UKBEventData* EventData)
{
	const UKBEventData_OnReqBagList* ServerData = Cast<UKBEventData_OnReqBagList>(EventData);

	for (auto Info : ServerData->MainBag) {
		FGoodInfo GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		UPtDataMgr::Get()->ChangeGoodInfo(EBagType::MainBag, GoodInfo);
	}

	for (auto Info : ServerData->SkillBag) {
		FGoodInfo GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		UPtDataMgr::Get()->ChangeGoodInfo(EBagType::SkillBag, GoodInfo);
	}

	for (auto Info : ServerData->BuffBag) {
		FGoodInfo GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		UPtDataMgr::Get()->ChangeGoodInfo(EBagType::BuffBag, GoodInfo);
	}

	for (auto Info : ServerData->EquipBag) {
		FGoodInfo GoodInfo;
		GoodInfo.InitInfo(Info.BlockId, Info.GoodId, Info.Number);
		UPtDataMgr::Get()->ChangeGoodInfo(EBagType::EquipBag, GoodInfo);
	}
}

void UPtMainGameWidget::OnIncreaseGood(const UKBEventData* EventData)
{
	const UKBEventData_OnIncreaseGood* ServerData = Cast<UKBEventData_OnIncreaseGood>(EventData);

	EBagType BagType = (EBagType)ServerData->BagType;
	FGoodInfo GoodInfo;
	GoodInfo.InitInfo(ServerData->GoodInfo.BlockId, ServerData->GoodInfo.GoodId, ServerData->GoodInfo.Number);

	//增加物品不存在传过来的物品为空的问题, 这里直接增加背包物品
	UPtDataMgr::Get()->ChangeGoodInfo(BagType, GoodInfo);
}

void UPtMainGameWidget::OnPassGood(const UKBEventData* EventData)
{
	const UKBEventData_OnPassGood* ServerData = Cast<UKBEventData_OnPassGood>(EventData);

	EBagType ArcBagType = (EBagType)ServerData->ArcBagType;
	FGoodInfo ArcGoodInfo;
	ArcGoodInfo.InitInfo(ServerData->ArcGoodInfo.BlockId, ServerData->ArcGoodInfo.GoodId, ServerData->ArcGoodInfo.Number);

	EBagType DesBagType = (EBagType)ServerData->DesBagType;
	FGoodInfo DesGoodInfo;
	DesGoodInfo.InitInfo(ServerData->DesGoodInfo.BlockId, ServerData->DesGoodInfo.GoodId, ServerData->DesGoodInfo.Number);

	//直接更新DataMgr的背包数据
	UPtDataMgr::Get()->ChangeGoodInfo(ArcBagType, ArcGoodInfo);
	UPtDataMgr::Get()->ChangeGoodInfo(DesBagType, DesGoodInfo);
}

void UPtMainGameWidget::OnReduceGood(const UKBEventData* EventData)
{
	const UKBEventData_OnReduceGood* ServerData = Cast<UKBEventData_OnReduceGood>(EventData);

	EReduceResult ReduceRes = (EReduceResult)ServerData->ReduceRes;

	//获取数据
	EBagType BagType = (EBagType)ServerData->BagType;
	FGoodInfo GoodInfo;
	GoodInfo.InitInfo(ServerData->GoodInfo.BlockId, ServerData->GoodInfo.GoodId, ServerData->GoodInfo.Number);

	if (ReduceRes == EReduceResult::Succeed) {
		//如果成功, 区分技能和buff来做效果
		if (GoodInfo.GoodType == EGoodType::Skill) {
			//告诉Character请求服务器进行攻击
			if (PlayerCharacter) {
				//PlayerCharacter->Attack(GoodInfo.GoodKind);
				PtH::Debug() << "PlayerCharacter using Skill" << PtH::Endl();
			}
		}
		else if (GoodInfo.GoodType == EGoodType::Buff) {
			//放点特效啥的, ToDo
			PtH::Debug() << "PlayerCharacter using Buff" << PtH::Endl();
		}
	}

	//无论是否成功都要更新背包物品,先更新数据
	UPtDataMgr::Get()->ChangeGoodInfo(BagType, GoodInfo);
}

void UPtMainGameWidget::UpdateBagBlock(EBagType BagType, uint8 BlockId)
{
	switch (BagType)
	{
	case EBagType::MainBag:
		MainBag->UpdateBlock(BlockId);
		break;
	case EBagType::SkillBag:
		SkillBag->UpdateBlock(BlockId);
		break;
	case EBagType::BuffBag:
		BuffBag->UpdateBlock(BlockId);
		break;
	case EBagType::EquipBag:
		EquipBag->UpdateBlock(BlockId);
		break;
	}
}

