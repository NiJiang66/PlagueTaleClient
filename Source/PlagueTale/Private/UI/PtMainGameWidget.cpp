// Fill out your copyright notice in the Description page of Project Settings.


#include "PtMainGameWidget.h"
#include "TextBlock.h"
#include "ProgressBar.h"
#include "Overlay.h"
#include "Engine/KBEngine.h"
#include "Scripts/PtEventData.h"

void UPtMainGameWidget::InstallEvents(FText RoomName)
{
	//设置房间名字
	RoomText->SetText(RoomName);

	//绑定背包方法等

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

void UPtMainGameWidget::ReliveEvent()
{
	//告诉服务端复活玩家，在KBEngine::PtRole::__init__注册
	KBENGINE_EVENT_FIRE("Relive", NewObject<UKBEventData>());
}



