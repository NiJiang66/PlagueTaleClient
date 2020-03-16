// Fill out your copyright notice in the Description page of Project Settings.


#include "PtBloodBar.h"
#include "Components/TextBlock.h"
#include "Components/ProgressBar.h"

void UPtBloodBar::SetHPPercent(float InPercent)
{
	BloodProgress->SetPercent(InPercent);
	BloodProgress->SetFillColorAndOpacity(FLinearColor(1.f - InPercent, InPercent, 0.f));
}

void UPtBloodBar::SetRole(uint8 RoleType, FString InName)
{
	if (RoleType == 0 || RoleType == 1) {
		NameText->SetColorAndOpacity(FLinearColor(0.f, 0.18f, 1.f));
	}
	else {
		NameText->SetColorAndOpacity(FLinearColor(1.f, 0.f, 0.f));
	}
	NameText->SetText(FText::FromString(InName));
}
