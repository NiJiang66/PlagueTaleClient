// Fill out your copyright notice in the Description page of Project Settings.


#include "PtRemotePlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"

FName APtRemotePlayerCharacter::GroundName(TEXT("Ground"));

APtRemotePlayerCharacter::APtRemotePlayerCharacter()
{
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	GroundBox = CreateDefaultSubobject<UBoxComponent>(TEXT("Ground"));
	GroundBox->SetupAttachment(RootComponent);
	GroundBox->SetCollisionProfileName(FName("OverlapAll"));

	//通过反射绑定GroundBox开始碰撞事件
	FScriptDelegate OverlapBegin;
	OverlapBegin.BindUFunction(this, "OnOverlapBegin");
	GroundBox->OnComponentBeginOverlap.Add(OverlapBegin);

	//通过反射绑定GroundBox结束碰撞事件
	FScriptDelegate OverlapEnd;
	OverlapEnd.BindUFunction(this, "OnOverlapEnd");
	GroundBox->OnComponentEndOverlap.Add(OverlapEnd);
}

void APtRemotePlayerCharacter::Tick(float DeltaTime)
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

void APtRemotePlayerCharacter::OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	//是否碰到地面
	if (OtherActor->GetFName().IsEqual(GroundName)) {
		IsInAir_Anim = false;
	}
}

void APtRemotePlayerCharacter::OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	//是否碰到地面
	if (OtherActor->GetFName().IsEqual(GroundName)) {
		IsInAir_Anim = true;
	}
}


