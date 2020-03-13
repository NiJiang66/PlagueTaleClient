// Fill out your copyright notice in the Description page of Project Settings.


#include "PtCommon.h"

TSharedPtr<PtRecord> PtRecord::RecordInst = NULL;

TSharedPtr<PtRecord> PtRecord::Get()
{
	if (!RecordInst.IsValid())
		RecordInst = MakeShareable(new PtRecord());
	return RecordInst;
}

UPtCommon* UPtCommon::PtInst = NULL;

UPtCommon* UPtCommon::Get()
{
	if (!PtInst)
	{
		PtInst = NewObject<UPtCommon>();
		PtInst->AddToRoot();
	}
	return PtInst;
}


