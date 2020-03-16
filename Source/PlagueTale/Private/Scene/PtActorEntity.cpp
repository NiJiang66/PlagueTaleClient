// Fill out your copyright notice in the Description page of Project Settings.


#include "PtActorEntity.h"
#include "ENgine/KBEngine.h"
#include "Engine/Entity.h"

APtActorEntity::APtActorEntity()
{
	PrimaryActorTick.bCanEverTick = true;

}

void APtActorEntity::SetTargetPosition(FVector InPos)
{
	TargetPosition = InPos;

	//获取本次更新时间间隔
	float UpdatePositionSpaceTime = GetWorld()->TimeSeconds - LastUpdatePositionTime;
	//更新上次更新时间
	LastUpdatePositionTime = GetWorld()->TimeSeconds;
	//获取距离
	float Distance = FVector::Dist(TargetPosition, GetActorLocation());
	//计算实时速度
	MoveSpeed = Distance / UpdatePositionSpaceTime;
}


void APtActorEntity::BeginPlay()
{
	Super::BeginPlay();

	// 由于UE4可视化实体创建要晚于KBE的插件的逻辑实体，而KBE插件实体先前可能已经触发了一些属性设置事件
	// 因此此时我们可能已经错过了一些事件，我们只能在此补救必要的触发了， 例如：血量速度属性值
	KBEngine::Entity* EntityInst = KBEngine::KBEngineApp::getSingleton().findEntity(EntityId);
	if (EntityInst) {
		EntityInst->callPropertysSetMethods();
	}
}


void APtActorEntity::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//更新位置
	FVector CurrentPosition = GetActorLocation();
	FVector TargetDirection = TargetPosition - CurrentPosition;

	float DeltaSpeed = DeltaTime * MoveSpeed;
	float Distance = TargetDirection.Size();

	//距离太大或者太小直接设置位置
	if (Distance < DeltaSpeed) {
		SetActorLocation(TargetPosition);
	}
	else {
		//移动位置
		TargetDirection.Normalize();
		SetActorLocation(CurrentPosition + (TargetDirection * DeltaSpeed));
	}
}

