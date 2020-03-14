// Fill out your copyright notice in the Description page of Project Settings.


#include "PtBaseCharacter.h"
#include "PtGameMode.h"
#include "Engine/KBEngine.h"
#include "Engine/Entity.h"
#include "Components/SkeletalMeshComponent.h"


// Sets default values
APtBaseCharacter::APtBaseCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	HP = 500;
}

// Called when the game starts or when spawned
void APtBaseCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	//如果不是玩家
	if (!IsPlayer && MainGameMode) {
		MainGameMode->OtherCharacters.Add(EntityId, this);
	}

	//初始化数据
	LastUpdatePositionTime = GetWorld()->TimeSeconds;
	LastUpdateAnimTime = GetWorld()->TimeSeconds;

	//刷新一次实体数据到UE4对象
	KBEngine::Entity* EntityInst = KBEngine::KBEngineApp::getSingleton().findEntity(EntityId);
	if (EntityInst) {
		EntityInst->callPropertysSetMethods();
	}

	//获取动作蓝图
	CharacterAnim = GetMesh()->GetAnimInstance();
}

void APtBaseCharacter::Destroyed()
{
	Super::Destroyed();

	//如果不是玩家
	if (!IsPlayer && MainGameMode) {
		MainGameMode->OtherCharacters.Remove(EntityId);
	}
}

void APtBaseCharacter::SetTargetPosition(FVector InPos)
{
	TargetPosition = InPos;

	//获取更新时间间隔
	float UpdatePositionSpaceTime = GetWorld()->TimeSeconds - LastUpdatePositionTime;
	//保存当前时间
	LastUpdatePositionTime = GetWorld()->TimeSeconds;
	//获取距离
	float Distance = FVector::Dist(TargetPosition, GetActorLocation());
	//计算出实时速度
	MoveSpeed = Distance / UpdatePositionSpaceTime;
}

void APtBaseCharacter::SetTargetRotator(FRotator InRot)
{
	TargetRotator = InRot;
}

void APtBaseCharacter::SetTargetAnim(float Speed, float Direction)
{
	//获取插值头尾状态
	TargetSpeed = Speed;
	TargetDirection = Direction;
	LastSpeed = Speed_Anim;
	LastDirection = Direction_Anim;

	//获取时间间隔
	UpdateAnimSpaceTime = GetWorld()->TimeSeconds - LastUpdateAnimTime;
	RemainAnimSpaceTime = UpdateAnimSpaceTime;
	//保留上一次更新的时间
	LastUpdateAnimTime = GetWorld()->TimeSeconds;
}

