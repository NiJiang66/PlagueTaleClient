// Fill out your copyright notice in the Description page of Project Settings.


#include "PtRemotePlayerCharacter.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "PtBloodBar.h"
#include "Animation/AnimInstance.h"
#include "PtDataMgr.h"

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

	BloodBarComponent = CreateDefaultSubobject<UWidgetComponent>(TEXT("BloodBar"));
	BloodBarComponent->SetupAttachment(RootComponent);
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

void APtRemotePlayerCharacter::SetBaseHP(int32 InBaseHP)
{
	//增加血值上限
	if (InBaseHP > BaseHP) {
		//直接保存到本地, 不进行血值的修改
		BaseHP = InBaseHP;
	}
	else if (InBaseHP < BaseHP) {
		//判断是否当前血值比新血值小
		if (HP > InBaseHP) {
			HP = InBaseHP;
			BaseHP = InBaseHP;
		}
	}

	//远端玩家要更新血条
	float HPPercent = FMath::Clamp((float)HP / (float)BaseHP, 0.f, 1.f);
	if (BloodBar) {
		BloodBar->SetHPPercent(HPPercent);
	}		
}

void APtRemotePlayerCharacter::SetHP(int32 InHP)
{
	if (InHP > 0 && InHP < BaseHP && HP != 0 && InHP != HP && CharacterAnim) {
		//播放受伤动画
		CharacterAnim->Montage_Play(HurtMontage);
	}

	HP = InHP;

	float HPPercent = FMath::Clamp((float)HP / (float)BaseHP, 0.f, 1.f);
	if (BloodBar){ BloodBar->SetHPPercent(HPPercent); }		
}

void APtRemotePlayerCharacter::OnAttack(uint8 SkillID)
{
	switch (SkillID)
	{
		case (int)ESkillType::Stone://寒冰之石
		{
			if (CharacterAnim) {
				CharacterAnim->Montage_Play(SkillIceStoneMontage);
			}
		}
		break;
		case (int)ESkillType::Thunder://雷霆之光
		{
			if (CharacterAnim) {
				CharacterAnim->Montage_Play(SkillLightThunderMontage);
			}
		}
		break;
		case (int)ESkillType::XBlade://无尽之刃
		{
			if (CharacterAnim) {
				CharacterAnim->Montage_Play(SkillInfinitySwordMontage);
			}
		}
		break;
		case (int)ESkillType::Therapy://恢复之术
		{
			if (CharacterAnim) {
				CharacterAnim->Montage_Play(SkillRestorationMontage);
			}
		}
		break;
		default:
			break;
	}
}

void APtRemotePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//获取血条
	BloodBar = Cast<UPtBloodBar>(BloodBarComponent->GetUserWidgetObject());
	//设置名字和类型
	BloodBar->SetRole(RoleType, RoleName);
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


