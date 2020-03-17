// Fill out your copyright notice in the Description page of Project Settings.


#include "PtRoomWidget.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/EditableTextBox.h"
#include "WidgetTree.h"

#include "PtRoomItem.h"
#include "Engine/KBEngine.h"
#include "Scripts/PtCommon.h"
#include "PTGameInstance.h"
#include "Kismet/GameplayStatics.h"



bool UPtRoomWidget::Initialize()
{
	if (!Super::Initialize())return false;

	//注册按钮点击事件
	EnterGameBtn->OnClicked.AddDynamic(this, &UPtRoomWidget::EnterGameEvent);
	RefreshBtn->OnClicked.AddDynamic(this, &UPtRoomWidget::RefreshRoomListEvent);
	CreateRoomBtn->OnClicked.AddDynamic(this, &UPtRoomWidget::CreateRoomEvent);
	return true;
}

void UPtRoomWidget::EnterGameEvent()
{
	for (int i = 0; i < RoomItemGroup.Num(); ++i) {
		if (RoomItemGroup[i]->IsSelected)
		{
			//保存选中的房间名称到GameInstance
			UPtGameInstance* GameInstance = Cast<UPtGameInstance>(UGameplayStatics::GetGameInstance(this));
			GameInstance->RoomName = FText::FromString(RoomItemGroup[i]->RoomInfo.Name);

			//通知服务器
			UKBEventData_SelectRoomGame* EventData = NewObject<UKBEventData_SelectRoomGame>();
			EventData->RoomId = RoomItemGroup[i]->RoomInfo.RoomId;
			KBENGINE_EVENT_FIRE("SelectRoomGame", EventData);
			return;
		}
	}
	PtH::Debug() << "Please Select Room" << PtH::Endl();
}

void UPtRoomWidget::RefreshRoomListEvent()
{
	KBENGINE_EVENT_FIRE("ReqRoomList", NewObject<UKBEventData>());
}

void UPtRoomWidget::CreateRoomEvent()
{
	//获取房间名字
	FString RoomName = RoomNameTextBox->GetText().ToString();
	RoomNameTextBox->SetText(FText());
	if (RoomName.IsEmpty()) {
		PtH::Debug() << "Please Enter Room Name" << PtH::Endl();
		return;
	}

	UKBEventData_ReqCreateRoom* EventData = NewObject<UKBEventData_ReqCreateRoom>();
	EventData->RoomName = RoomName;

	KBENGINE_EVENT_FIRE("ReqCreateRoom", EventData);
}

void UPtRoomWidget::OnReqRoomList(TArray<FROOM_INFO> RoomList)
{
	//把旧的列表移除
	for (int i = 0; i < RoomItemGroup.Num(); ++i) {
		RoomItemGroup[i]->RemoveFromParent();
		RoomItemGroup[i]->ConditionalBeginDestroy();
	}
	//清空数组
	RoomItemGroup.Empty();

	//循环创建RoomItem
	for (int i = 0; i < RoomList.Num(); ++i) {
		// 创建RoomItem
		UPtRoomItem* RoomItem = WidgetTree->ConstructWidget<UPtRoomItem>(RoomItemClass);
		UScrollBoxSlot* RoomItemSlot = Cast<UScrollBoxSlot>(RoomListScroll->AddChild(RoomItem));
		//RoomItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

		// 设置房间信息
		RoomItem->InitItem(RoomList[i]);
		RoomItem->RoomItemSelectDel.BindUObject(this, &UPtRoomWidget::RoomItemSelect);

		// 保存房间条目到本地数组
		RoomItemGroup.Add(RoomItem);
	}

	//如果只有一个房间, 直接选中该房间
	if (RoomItemGroup.Num() == 1) {
		RoomItemSelect(RoomItemGroup[0]->RoomInfo.RoomId);
	}
}

void UPtRoomWidget::OnCreateRoom(FROOM_INFO RoomInfo)
{
	// 创建RoomItem
	UPtRoomItem* RoomItem = WidgetTree->ConstructWidget<UPtRoomItem>(RoomItemClass);
	UScrollBoxSlot* RoomItemSlot = Cast<UScrollBoxSlot>(RoomListScroll->AddChild(RoomItem));
	//RoomItemSlot->SetPadding(FMargin(0.f, 5.f, 0.f, 5.f));

	// 设置房间信息
	RoomItem->InitItem(RoomInfo);
	RoomItem->RoomItemSelectDel.BindUObject(this, &UPtRoomWidget::RoomItemSelect);

	// 保存房间条目到本地数组
	RoomItemGroup.Add(RoomItem);

	//如果只有一个房间, 直接选中该房间
	if (RoomItemGroup.Num() == 1) {
		RoomItemSelect(RoomItemGroup[0]->RoomInfo.RoomId);
	}
}

void UPtRoomWidget::RoomItemSelect(uint64 RoomId)
{
	for (int i = 0; i < RoomItemGroup.Num(); ++i) {
		if (RoomItemGroup[i]->RoomInfo.RoomId != RoomId) {
			RoomItemGroup[i]->UnItemSelect();
		}			
		else {
			RoomItemGroup[i]->ItemSelect();
		}			
	}
}
