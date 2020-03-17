// Fill out your copyright notice in the Description page of Project Settings.


#include "PtFlobActor.h"
#include "PtGameMode.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Components/StaticMeshComponent.h"
#include "PtDataMgr.h"



APtFlobActor::APtFlobActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

	BaseMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
	BaseMesh->SetupAttachment(RootComponent);
}

void APtFlobActor::BeginPlay()
{
	Super::BeginPlay();

	if (MainGameMode) {
		MainGameMode->FlobMap.Add(EntityId, this);
	}

	UTexture* GoodTexture = UPtDataMgr::Get()->GetGoodTexture(GoodId);
	//设置图片
	BaseMatInst = UMaterialInstanceDynamic::Create(BaseMat, nullptr);
	BaseMatInst->SetTextureParameterValue(FName("BaseTex"), GoodTexture);

	BaseMesh->SetMaterial(0, BaseMatInst);
}

void APtFlobActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// 一直旋转
	BaseMesh->AddLocalRotation(FRotator(DeltaTime * 100.f, 0.f, 0.f));
}

void APtFlobActor::Destroyed()
{
	Super::Destroyed();

	//从GameMode移除
	if (MainGameMode) {
		MainGameMode->FlobMap.Remove(EntityId);
	}
}
