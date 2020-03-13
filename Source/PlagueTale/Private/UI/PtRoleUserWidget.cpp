// Fill out your copyright notice in the Description page of Project Settings.


#include "PtRoleUserWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/HorizontalBox.h"
#include "Components/EditableTextBox.h"
#include "Components/CheckBox.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "WidgetTree.h"
#include "PtRoleItem.h"

#include "PtRoleGameMode.h"
#include "Scripts/PtCommon.h"
#include "Kismet/GameplayStatics.h"
#include "Scene/PtRenderActor.h"


bool UPtRoleUserWidget::Initialize()
{
	if (!Super::Initialize())return false;

	//注册按钮点击事件
	EnterGameBtn->OnClicked.AddDynamic(this, &UPtRoleUserWidget::EnterGameEvent);
	CreateRoleBtn->OnClicked.AddDynamic(this, &UPtRoleUserWidget::CreateRoleEvent);
	RemoveRoleBtn->OnClicked.AddDynamic(this, &UPtRoleUserWidget::RemoveRoleEvent);
	SureBtn->OnClicked.AddDynamic(this, &UPtRoleUserWidget::SureEvent);
	CancelBtn->OnClicked.AddDynamic(this, &UPtRoleUserWidget::CancelEvent);
	return true;
}

void UPtRoleUserWidget::EnterGameEvent()
{
	APtRoleGameMode* RoleGameMode = Cast<APtRoleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (RoleGameMode == nullptr) {
		PtH::Debug() << "RoleGameMode is NULL" << PtH::Endl();
		return;
	}
	//找出选中的那个角色
	for (int i = 0; i < LocalRoleItemGroup.Num(); ++i) {
		if (LocalRoleItemGroup[i]->RoleInfo.IsLastRole) {
			RoleGameMode->SelectRoleGame(LocalRoleItemGroup[i]->RoleInfo);
			return;
		}
	}
}

void UPtRoleUserWidget::CreateRoleEvent()
{
	//显示角色类型选择框、角色名输入框、确定取消按钮
	EnterGameBtn->SetVisibility(ESlateVisibility::Hidden);
	RoleTypeBox->SetVisibility(ESlateVisibility::Visible);

	CreateRoleBtn->SetVisibility(ESlateVisibility::Hidden);
	RoleNameTextBox->SetVisibility(ESlateVisibility::Visible);

	RemoveRoleBtn->SetVisibility(ESlateVisibility::Hidden);
	SureBtn->SetVisibility(ESlateVisibility::Visible);
	CancelBtn->SetVisibility(ESlateVisibility::Visible);
}

void UPtRoleUserWidget::RemoveRoleEvent()
{
	APtRoleGameMode* RoleGameMode = Cast<APtRoleGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (RoleGameMode == nullptr) {
		PtH::Debug() << "RoleGameMode is NULL" << PtH::Endl();
		return;
	}
	for (int i = 0; i < LocalRoleItemGroup.Num(); ++i) {
		if (LocalRoleItemGroup[i]->RoleInfo.IsLastRole) {
			RoleGameMode->ReqRemoveRole(LocalRoleItemGroup[i]->RoleInfo);
			return;
		}
	}

	//如果运行到这里说明没有选中任何角色
	PtH::Debug() << "UExRoleWidget::RemoveRoleEvent : No Role Selected" << PtH::Endl();
}

void UPtRoleUserWidget::SureEvent()
{
	//显示进入游戏、创建角色、删除角色按钮
	EnterGameBtn->SetVisibility(ESlateVisibility::Visible);
	RoleTypeBox->SetVisibility(ESlateVisibility::Hidden);

	CreateRoleBtn->SetVisibility(ESlateVisibility::Visible);
	RoleNameTextBox->SetVisibility(ESlateVisibility::Hidden);

	RemoveRoleBtn->SetVisibility(ESlateVisibility::Visible);
	SureBtn->SetVisibility(ESlateVisibility::Hidden);
	CancelBtn->SetVisibility(ESlateVisibility::Hidden);


	//创建新角色
	FString RoleName = RoleNameTextBox->GetText().ToString();

	if (RoleName.IsEmpty())	{
		PtH::Debug() << "Please Enter Role Name" << PtH::Endl();
		return;
	}

	//这里只是临时使用两个角色的简便方法
	uint8 Roletype = ShooterCheckBox->GetCheckedState() == ECheckBoxState::Checked ? 0 : 1;

	APtRoleGameMode* RoleGameMode = Cast<APtRoleGameMode>(UGameplayStatics::GetGameMode(this));
	if (RoleGameMode) {
		RoleGameMode->ReqCreateRole(Roletype, RoleName);
	}	

	//清空名字输入框
	RoleNameTextBox->SetText(FText());
}

void UPtRoleUserWidget::CancelEvent()
{
	//显示进入游戏、创建角色、删除角色按钮
	EnterGameBtn->SetVisibility(ESlateVisibility::Visible);
	RoleTypeBox->SetVisibility(ESlateVisibility::Hidden);

	CreateRoleBtn->SetVisibility(ESlateVisibility::Visible);
	RoleNameTextBox->SetVisibility(ESlateVisibility::Hidden);

	RemoveRoleBtn->SetVisibility(ESlateVisibility::Visible);
	SureBtn->SetVisibility(ESlateVisibility::Hidden);
	CancelBtn->SetVisibility(ESlateVisibility::Hidden);

	//清空名字输入框
	RoleNameTextBox->SetText(FText());
}

void UPtRoleUserWidget::OnReqRoleList(TArray<FROLE_INFO> RoleList)
{
	for (int i = 0; i < RoleList.Num(); ++i) {
		//创建RoleItem
		UPtRoleItem* RoleItem = WidgetTree->ConstructWidget<UPtRoleItem>(RoleItemClass);
		UScrollBoxSlot* RISlot = Cast<UScrollBoxSlot>(RoleItemScroll->AddChild(RoleItem));
		RISlot->SetPadding(FMargin(0, 5, 0, 5));
		//设置角色信息
		RoleItem->InitItem(RoleList[i]);
		RoleItem->RoleItemSelectDel.BindUObject(this, &UPtRoleUserWidget::RoleItemSelect);
		//保存角色条目到本地数组
		LocalRoleItemGroup.Add(RoleItem);
	}
}

void UPtRoleUserWidget::OnCreateRoleResult(FROLE_INFO RoleInfo)
{
	//创建RoleItem添加到界面
	UPtRoleItem* RoleItem = WidgetTree->ConstructWidget<UPtRoleItem>(RoleItemClass);
	UScrollBoxSlot* RISlot = Cast<UScrollBoxSlot>(RoleItemScroll->AddChild(RoleItem));
	RISlot->SetPadding(FMargin(0, 5, 0, 5));
	//设置角色信息
	RoleItem->InitItem(RoleInfo);
	RoleItem->RoleItemSelectDel.BindUObject(this, &UPtRoleUserWidget::RoleItemSelect);
	//保存角色条目到本地数组
	LocalRoleItemGroup.Add(RoleItem);
	//如果当前只有一个角色，就选中该角色
	if (LocalRoleItemGroup.Num() == 1) {
		RoleItemSelect(RoleInfo.Dbid);
	}
}

void UPtRoleUserWidget::OnRemoveRole(FROLE_INFO RoleInfo)
{
	//获取待移除的角色
	UPtRoleItem* RoleItem = nullptr;
	for (int i = 0; i < LocalRoleItemGroup.Num(); ++i) {
		if (LocalRoleItemGroup[i]->RoleInfo.Dbid == RoleInfo.Dbid) {
			RoleItem = LocalRoleItemGroup[i];
		}
	}
	if (!RoleItem) {
		PtH::Debug() << "UExRoleWidget::OnRemoveRole : No RoleInfo Wxit By Dbid --> " << RoleInfo.Dbid << PtH::Endl();
		return;
	}
	//移除RoleItem
	RoleItemScroll->RemoveChild(RoleItem);
	LocalRoleItemGroup.Remove(RoleItem);

	//如果角色列表不为空，设置选中第一个
	if (LocalRoleItemGroup.Num() > 0) {
		RoleItemSelect(0);
	}		
}

void UPtRoleUserWidget::RoleItemSelect(uint64 Dbid)
{
	APtRoleGameMode* RoleGameMode = Cast<APtRoleGameMode>(UGameplayStatics::GetGameMode(this));

	//取消其他角色的选定
	for (int i = 0; i < LocalRoleItemGroup.Num(); ++i) {
		if (LocalRoleItemGroup[i]->RoleInfo.Dbid != Dbid) {
			LocalRoleItemGroup[i]->UnItemSelect();
		}			
		else {
			LocalRoleItemGroup[i]->ItemSelect();
			//设置选中的角色, 0 : 射手 ; 1 : 法师
			RoleTypeTitle->SetText(FText::FromString(RoleTypeName[LocalRoleItemGroup[i]->RoleInfo.RoleType]));
			//渲染角色图片
			if (RoleGameMode) {
				RoleGameMode->RenderActor->SwitchRoleMesh(LocalRoleItemGroup[i]->RoleInfo.RoleType);
			}			
		}
	}
}
