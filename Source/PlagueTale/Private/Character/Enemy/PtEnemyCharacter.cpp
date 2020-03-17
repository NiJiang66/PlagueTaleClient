// Fill out your copyright notice in the Description page of Project Settings.


#include "PtEnemyCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/WidgetComponent.h"
#include "PtBloodBar.h"
#include "Engine/World.h"
#include "Animation/AnimInstance.h"
#include "Scripts/PtCommon.h"
#include "TimerManager.h"

APtEnemyCharacter::APtEnemyCharacter()
{
	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));
	BloodBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("BloodBar"));
	BloodBarComponent->SetupAttachment(RootComponent);
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

void APtEnemyCharacter::PlayDeath()
{
	//动画由状态机自己判定HP是否小于0来播放
	//延时销毁
	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, this, &APtEnemyCharacter::MonsterDestroy, 5.f);
}

void APtEnemyCharacter::SetHP(int32 InHP)
{
	if (InHP > 0 && InHP < BaseHP && HP!=0 && InHP!=HP && CharacterAnim) {
		//播放受伤动画
		CharacterAnim->Montage_Play(HurtMontage);
	}

	HP = InHP;
	float HPPercent = FMath::Clamp((float)HP / (float)BaseHP, 0.f, 1.f);
	if (BloodBar) {
		BloodBar->SetHPPercent(HPPercent);
	}
}

void APtEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	//获取血条
	BloodBar = Cast<UPtBloodBar>(BloodBarComponent->GetUserWidgetObject());
	//设置名字和类型
	BloodBar->SetRole(RoleType, RoleName);
}

void APtEnemyCharacter::MonsterDestroy()
{
	Destroy();
}