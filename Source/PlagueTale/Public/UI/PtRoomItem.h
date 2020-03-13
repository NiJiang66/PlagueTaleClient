// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Scripts/PtEventData.h"
#include "PtRoomItem.generated.h"

class UImage;
class UButton;
class UTextBlock;

/**	定义房间条目选中代理，参数为Bdid */
DECLARE_DELEGATE_OneParam(FRoomItemSelect, uint64)

/**
 * 房间列表的条目
 */
UCLASS()
class PLAGUETALE_API UPtRoomItem : public UUserWidget
{
	GENERATED_BODY()
public:

	/** 绑定该UI控件的代理事件 */
	virtual bool Initialize() override;

	/**	触发角色条目选中时代理事件 */
	UFUNCTION()
	void ItemButtonEvent();

	/**	初始化角色条目信息 */
	void InitItem(FROOM_INFO InRoomInfo);

	/**	选择条目 */
	void ItemSelect();
	/**	取消选择条目 */
	void UnItemSelect();


public:
	/**	保存用于显示选中效果的图片 */
	UPROPERTY(Meta = (BindWidget))
	UImage* OutLineImg;

	/**	保存条目按钮 */
	UPROPERTY(Meta = (BindWidget))
	UButton* ItemBtn;

	/**	保存房间名称 */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* ItemName;

	/**	房间信息 */
	UPROPERTY()
	FROOM_INFO RoomInfo;

	/**	房间条目选中代理，参数为Bdid */
	FRoomItemSelect RoomItemSelectDel;

	/**	保存是否被选中 */
	bool IsSelected;
};
