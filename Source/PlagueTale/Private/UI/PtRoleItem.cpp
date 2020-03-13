// Fill out your copyright notice in the Description page of Project Settings.


#include "PtRoleItem.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "Components/Button.h"



bool UPtRoleItem::Initialize()
{
	if (!Super::Initialize())return false;

	//注册按钮点击事件
	ItemBtn->OnClicked.AddDynamic(this, &UPtRoleItem::ItemButtonEvent);

	return true;
}

void UPtRoleItem::ItemButtonEvent()
{
	RoleItemSelectDel.ExecuteIfBound(RoleInfo.Dbid);
}

void UPtRoleItem::InitItem(FROLE_INFO InRoleInfo)
{
	RoleInfo = InRoleInfo;
	ItemName->SetText(FText::FromString(RoleInfo.Name));
	//如果该角色是上次就被选中的, 设置选定
	if (RoleInfo.IsLastRole) {
		ItemButtonEvent();
	}
}

void UPtRoleItem::ItemSelect()
{
	RoleInfo.IsLastRole = true;
	OutLineImg->SetVisibility(ESlateVisibility::Visible);
}

void UPtRoleItem::UnItemSelect()
{
	RoleInfo.IsLastRole = false;
	OutLineImg->SetVisibility(ESlateVisibility::Collapsed);
}

