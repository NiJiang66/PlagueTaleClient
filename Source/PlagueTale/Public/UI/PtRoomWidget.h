// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Scripts/PtEventData.h"
#include "PtRoomWidget.generated.h"

class UScrollBox;
class UEditableTextBox;
class UPtRoomItem;
class UButton;

/**
 * 房间选择界面
 */
UCLASS()
class PLAGUETALE_API UPtRoomWidget : public UUserWidget
{
	GENERATED_BODY()
public:
	/** 绑定该UI控件的代理事件 */
	virtual bool Initialize() override;

	/**	进入游戏事件 */
	UFUNCTION()
	void EnterGameEvent();
	/**	刷新房间列表事件 */
	UFUNCTION()
	void RefreshRoomListEvent();
	/**	创建房间事件 */
	UFUNCTION()
	void CreateRoomEvent();

	/**	KBE事件，请求房间列表回调函数的回调函数 */
	void OnReqRoomList(TArray<FROOM_INFO> RoomList);
	/**	KBE事件，创建房间结果回调函数的回调函数 */
	void OnCreateRoom(FROOM_INFO RoomInfo); 

protected:
	/**	房间条目被选中时的回调 */
	void RoomItemSelect(uint64 RoomId);

public:
	/**	选房间界面上的房间列表条目类型 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPtRoomItem> RoomItemClass;
	/** 保存房间列表数据 */
	UPROPERTY()
	TArray<UPtRoomItem*> RoomItemGroup;

	/**	房间列表 */
	UPROPERTY(Meta = (BindWidget))
	UScrollBox* RoomListScroll;

	/**	房间名称输入框 */
	UPROPERTY(Meta = (BindWidget))
	UEditableTextBox* RoomNameTextBox;

	UPROPERTY(Meta = (BindWidget))
	UButton* EnterGameBtn;
	UPROPERTY(Meta = (BindWidget))
	UButton* RefreshBtn;
	UPROPERTY(Meta = (BindWidget))
	UButton* CreateRoomBtn;
};
