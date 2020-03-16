// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PtBloodBar.generated.h"

class UTextBlock;
class UProgressBar;

/**
 * 世界中的血条和名字的Widget
 */
UCLASS()
class PLAGUETALE_API UPtBloodBar : public UUserWidget
{
	GENERATED_BODY()
public:
	/**	设置HP百分比 */
	void SetHPPercent(float InPercent);

	/**	设置角色文字颜色 */
	void SetRole(uint8 RoleType, FString InName);

public:
	/**	保存名字文本 */
	UPROPERTY(Meta = (BindWidget))
	UTextBlock* NameText;

	/**	保存血条 */
	UPROPERTY(Meta = (BindWidget))
	UProgressBar* BloodProgress;
};
