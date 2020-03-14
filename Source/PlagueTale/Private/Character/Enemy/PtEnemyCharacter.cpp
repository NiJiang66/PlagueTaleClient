// Fill out your copyright notice in the Description page of Project Settings.


#include "PtEnemyCharacter.h"
#include "Components/SkeletalMeshComponent.h"

APtEnemyCharacter::APtEnemyCharacter()
{
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
}

void APtEnemyCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//更新位置
	FVector CurrentPosition = GetActorLocation();
	FVector MoveDirection = TargetPosition - CurrentPosition;

	float DeltaDistance = DeltaTime * MoveSpeed;
	float Distance = MoveDirection.Size();

	//距离太大或者太小直接设置位置
	if (Distance > 300.f || Distance < DeltaDistance) {
		SetActorLocation(TargetPosition);
	}
	else {
		//移动位置
		MoveDirection.Normalize();
		SetActorLocation(CurrentPosition + MoveDirection * DeltaDistance);
	}

	//更新旋转
	FRotator CurrentRotation = FMath::RInterpTo(GetActorRotation(), TargetRotator, DeltaTime, 10.f);
	FaceRotation(CurrentRotation);

	//更新动画
	RemainAnimSpaceTime -= DeltaTime * 5;//5倍是为了让动画加快更新至最新状态
	float AnimLerpPercent = FMath::Clamp(RemainAnimSpaceTime / UpdateAnimSpaceTime, 0.f, 1.f);
	Speed_Anim = FMath::Lerp(TargetSpeed, LastSpeed, AnimLerpPercent);
	Direction_Anim = FMath::Lerp(TargetDirection, LastDirection, AnimLerpPercent);
}
