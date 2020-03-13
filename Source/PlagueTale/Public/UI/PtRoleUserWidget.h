// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Scripts/PtEventData.h"
#include "PtRoleUserWidget.generated.h"

class UButton;
class UCheckBox;
class UHorizontalBox;
class UEditableTextBox;
class UTextBlock;
class UScrollBox;
class UPtRoleItem;

/**
 * 选择角色界面
 */
UCLASS()
class PLAGUETALE_API UPtRoleUserWidget : public UUserWidget
{
	GENERATED_BODY()

public:

	/** 绑定该UI控件的代理事件 */
	virtual bool Initialize() override;

	/** 进入游戏事件 */
	UFUNCTION()
	void EnterGameEvent();
	/** 开始创建角色事件 */
	UFUNCTION()
	void CreateRoleEvent();
	/** 删除角色事件 */
	UFUNCTION()
	void RemoveRoleEvent();
	/**	确认创建角色事件 */
	UFUNCTION()
	void SureEvent();
	/**	取消创建角色事件 */
	UFUNCTION()
	void CancelEvent();

	/**	请求角色列表回调函数 */
	void OnReqRoleList(TArray<FROLE_INFO> RoleList);
	/**	请求创建角色回调函数 */
	void OnCreateRoleResult(FROLE_INFO RoleInfo);
	/**	请求删除角色回调函数 */
	void OnRemoveRole(FROLE_INFO RoleInfo);

protected:
	/**	当角色条目被选中 */
	void RoleItemSelect(uint64 Dbid);

protected:
	/**	保存所有角色条目 */
	UPROPERTY()
	TArray<UPtRoleItem*> LocalRoleItemGroup;

public:
	/**	选角界面上的角色列表条目类型 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UPtRoleItem> RoleItemClass;

	/** 角色列表 */
	UPROPERTY(Meta = (BindWidget))
	UScrollBox* RoleItemScroll;

	/** 用选择角色类型，只需要获取一个CheckBox就行, 因为只有两个，目前就这样吧 */
	UPROPERTY(Meta = (BindWidget), BlueprintReadWrite, EditAnywhere)
	UCheckBox* ShooterCheckBox;

	/** 角色类型标题 */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* RoleTypeTitle;

	/**	保存两个角色类型名字 0 : 射手 ; 1 : 法师。 目前在此类对应的蓝图里维护 */
	UPROPERTY(EditAnywhere)
	TArray<FString> RoleTypeName;

	/**	按钮 */
	UPROPERTY(Meta = (BindWidget))
	UButton* EnterGameBtn;
	UPROPERTY(Meta = (BindWidget))
	UButton* CreateRoleBtn;
	UPROPERTY(Meta = (BindWidget))
	UButton* RemoveRoleBtn;

	UPROPERTY(Meta = (BindWidget))
	UButton* SureBtn;
	UPROPERTY(Meta = (BindWidget))
	UButton* CancelBtn;


	/**	该Box里保存用于选择角色类型的CheckBox */
	UPROPERTY(Meta = (BindWidget))
	UHorizontalBox* RoleTypeBox;

	/** 名字输入框 */
	UPROPERTY(Meta = (BindWidget))
	UEditableTextBox* RoleNameTextBox;

};
