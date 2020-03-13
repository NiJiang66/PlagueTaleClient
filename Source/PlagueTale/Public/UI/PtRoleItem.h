// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Scripts/PtEventData.h"
#include "PtRoleItem.generated.h"

class UImage;
class UButton;
class UTextBlock;

/**	定义角色条目选中代理，参数为Bdid */
DECLARE_DELEGATE_OneParam(FRoleItemSelect, uint64)

/**
 * 选角界面上的角色列表条目
 */
UCLASS()
class PLAGUETALE_API UPtRoleItem : public UUserWidget
{
	GENERATED_BODY()

public:

	/** 绑定该UI控件的代理事件 */
	virtual bool Initialize() override;

	/**	触发角色条目选中时代理事件 */
	UFUNCTION(BlueprintCallable)
	void ItemButtonEvent();

	/**	初始化角色条目信息 */
	void InitItem(FROLE_INFO InRoleInfo);

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

	/**	保存角色类型名称 */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* ItemName;

	/**	角色信息 */
	UPROPERTY()
	FROLE_INFO RoleInfo;

	/**	角色条目选中代理，参数为Bdid */
	FRoleItemSelect RoleItemSelectDel;

};
