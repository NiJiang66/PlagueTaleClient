// Fill out your copyright notice in the Description page of Project Settings.


#include "PtPlayerCharacter.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Components/InputComponent.h"
#include "PtPlayerController.h"
#include "Scripts/PtEventData.h"
#include "Animation/AnimInstance.h"
#include "PTBaseCharacter.h"
#include "PtMainGameWidget.h"
#include "TimerManager.h"
#include "PtDataMgr.h"
#include "Scripts/PtCommon.h"

APtPlayerCharacter::APtPlayerCharacter()
{
	TurnRate = LookUpRate = 30.f;

	GetMesh()->SetRelativeRotation(FRotator(0.f, -90.f, 0.f));

	//设置角色移动的朝向
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 540.f, 0.f);
	GetCharacterMovement()->JumpZVelocity = 600.f;
	GetCharacterMovement()->AirControl = 0.2f;

	//设置角色控制器是否控制朝向
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;//true
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(RootComponent);
	CameraBoom->TargetArmLength = 600.0f; // The camera follows at this distance behind the character	
	CameraBoom->bUsePawnControlRotation = true; // Rotate the arm based on the controller
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 120.f));
	// 防止手臂遮挡
	CameraBoom->bDoCollisionTest = true;
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>("FollowCamera");
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	//相机角色控制器控制朝向
	FollowCamera->bUsePawnControlRotation = true;

	//技能射出点
	SkillPoint = CreateDefaultSubobject<USceneComponent>(TEXT("SkillPoint"));
	SkillPoint->SetupAttachment(RootComponent);
}

void APtPlayerCharacter::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	//获取动作蓝图参数
	Speed_Anim = GetVelocity().Size();
	IsInAir_Anim = GetMovementComponent()->IsFalling();

	//获取移动角度
	float PreDir = GetVelocity().ToOrientationRotator().Yaw - GetActorRotation().Yaw;
	if (PreDir > 180.f) { PreDir -= 360.f; }		
	if (PreDir < -180.f) { PreDir += 360.f; }	
	//速度太小, 移动角度为0
	if (Speed_Anim < 5.f) { Direction_Anim = 0.f; }
	else { Direction_Anim = PreDir; }		
}

void APtPlayerCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &APtPlayerCharacter::DoJump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &APtPlayerCharacter::DoStopJump);

	PlayerInputComponent->BindAxis("MoveForward", this, &APtPlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &APtPlayerCharacter::MoveRight);

	PlayerInputComponent->BindAxis("Turn", this, &APtPlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APtPlayerCharacter::LookUp);

	PlayerInputComponent->BindAction("OperateBag", IE_Pressed, this, &APtPlayerCharacter::OperateBag);
	PlayerInputComponent->BindAction("WriteMessage", IE_Pressed, this, &APtPlayerCharacter::StartWriteMessage);

	PlayerInputComponent->BindAction("NormalAttack", IE_Released, this, &APtPlayerCharacter::RequestNormalAttack);

	PlayerInputComponent->BindAction("SkillOne", IE_Pressed, this, &APtPlayerCharacter::SkillOne);
	PlayerInputComponent->BindAction("SkillTwo", IE_Pressed, this, &APtPlayerCharacter::SkillTwo);
	PlayerInputComponent->BindAction("SkillThree", IE_Pressed, this, &APtPlayerCharacter::SkillThree);
	PlayerInputComponent->BindAction("SkillFour", IE_Pressed, this, &APtPlayerCharacter::SkillFour);

	PlayerInputComponent->BindAction("BuffOne", IE_Pressed, this, &APtPlayerCharacter::BuffOne);
	PlayerInputComponent->BindAction("BuffTwo", IE_Pressed, this, &APtPlayerCharacter::BuffTwo);
	PlayerInputComponent->BindAction("BuffThree", IE_Pressed, this, &APtPlayerCharacter::BuffThree);

}

void APtPlayerCharacter::SetBaseHP(int32 InBaseHP)
{
	BaseHP = InBaseHP;
}

void APtPlayerCharacter::SetHP(int32 InHP)
{
	if (InHP < 0) { InHP = 0; }

	//如果新血值为0, 就血值不为0, 说明死亡
	if (InHP == 0 && HP > 0) {
		//切换输入模式为UI
		MainController->SwitchInputMode(true);
	}

	//如果旧血值为0, 新血值大于0, 说明复活
	if (InHP > 0 && HP == 0) {
		//切换输入模式为Game
		MainController->SwitchInputMode(false);
	}

	//新的血值不为0, 并且比就血值小, 而且不等于基础血值
	if (InHP > 0 && InHP < HP && InHP != BaseHP) {
		//播放受伤动画
		CharacterAnim->Montage_Play(HurtMontage);
	}

	//保存血值
	HP = InHP;
}

void APtPlayerCharacter::SetSpeedRatio(float InSpeedRatio)
{
	GetCharacterMovement()->MaxWalkSpeed = 600 * InSpeedRatio;
}

void APtPlayerCharacter::Attack(uint8 SkillId)
{
	if (HP <= 0 || IsInAir_Anim) {
		return;
	}
	if (MainController) {
		//设置角色朝向
		SetActorRotation(FRotator(0, MainController->GetControlRotation().Yaw, 0));

		FVector2D ScreenSize = GEngine->GameViewport->Viewport->GetSizeXY();
		//获取射线起始点和方向
		FVector RayStartPos;
		FVector RayDirection;
		MainController->DeprojectScreenPositionToWorld(ScreenSize.X * 0.5f, ScreenSize.Y * 0.42f, RayStartPos, RayDirection);

		//进行射线检测
		FCollisionQueryParams TraceParams(true);
		TraceParams.AddIgnoredActor(this);
		TraceParams.bReturnPhysicalMaterial = false;
		TraceParams.bTraceComplex = true;

		FVector SpawnPos = SkillPoint->GetComponentLocation();
		FVector TargetPos;

		//如果射线检测到对象
		FHitResult HitResult(ForceInit);
		if (GetWorld()->LineTraceSingleByChannel(HitResult, RayStartPos, RayStartPos + RayDirection * 10000.f, ECollisionChannel::ECC_GameTraceChannel1, TraceParams)) {
			//更新射中点			
			if (SkillId == (uint8)ESkillType::Stone) {
				TargetPos = HitResult.Location;
			}
			else {
				SpawnPos = HitResult.Location;
				TargetPos = HitResult.Location;
			}
		}
		else {
			if (SkillId == (uint8)ESkillType::Stone) {
				//如果射线没有检测到对象,设置最远距离1000
				TargetPos = RayStartPos + RayDirection * 5000.f;
			}
			else {
				TargetPos = SkillPoint->GetComponentLocation();
			}			
		}

		UKBEventData_Attack* EventData = NewObject<UKBEventData_Attack>();
		EventData->SkillId = SkillId;
		EventData->SpawnPos = SpawnPos;
		EventData->TargetPos = TargetPos;
		//通知服务器
		KBENGINE_EVENT_FIRE("Attack", EventData);
	}
}

void APtPlayerCharacter::OnAttack(uint8 SkillID)
{
	switch (SkillID)
	{
	case (int)ESkillType::Stone ://寒冰之石
	{
		if (CharacterAnim) {
			CharacterAnim->Montage_Play(SkillIceStoneMontage);
		}		
	}
	break;
	case (int)ESkillType::Thunder ://雷霆之光
	{
		if (CharacterAnim) {
			CharacterAnim->Montage_Play(SkillLightThunderMontage);
		}
	}
	break;	
	case (int)ESkillType::XBlade ://无尽之刃
	{
		if (CharacterAnim) {
			CharacterAnim->Montage_Play(SkillInfinitySwordMontage);
		}
	}
	break;
	case (int)ESkillType::Therapy ://恢复之术
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

void APtPlayerCharacter::DoJump()
{
	Jump();
}

void APtPlayerCharacter::DoStopJump()
{
	StopJumping();
}

void APtPlayerCharacter::MoveForward(float Value)
{
	if (MainController && Value != 0.f) {
		const FRotator YawRotation(0, MainController->GetControlRotation().Yaw, 0); 
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
		AddMovementInput(Direction, Value);
	}
}

void APtPlayerCharacter::MoveRight(float Value)
{
	if (MainController && Value != 0.f) {
		const FRotator YawRotation(0, MainController->GetControlRotation().Yaw, 0);
		const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
		AddMovementInput(Direction, Value);
	}
}

void APtPlayerCharacter::Turn(float Value)
{	
	AddControllerYawInput(Value * TurnRate * GetWorld()->GetDeltaSeconds());
}

void APtPlayerCharacter::LookUp(float Value)
{
	AddControllerPitchInput(Value * LookUpRate * GetWorld()->GetDeltaSeconds());
}

void APtPlayerCharacter::AnimUpdate()
{
	UKBEventData_AnimUpdate* EventData = NewObject<UKBEventData_AnimUpdate>();
	EventData->Speed = Speed_Anim;
	EventData->Direction = Direction_Anim;
	//通知服务端更新动画
	KBENGINE_EVENT_FIRE("AnimUpdate", EventData);
}

void APtPlayerCharacter::OperateBag()
{
	//如果血值为0, 不允许操作
	if (HP == 0) {
		return;
	}		

	IsShowBag = !IsShowBag;
	//切换输入模式
	if (MainController) {
		MainController->SwitchInputMode(IsShowBag);
	}
	//通知MainGameWidget显示隐藏背包UI
	if (MainGameWidget) {
		MainGameWidget->OpenOrCloseBag(IsShowBag);
	}
}

void APtPlayerCharacter::StartWriteMessage()
{
	if (MainGameWidget) {
		MainGameWidget->StartWriteMessage();		
	}
}

void APtPlayerCharacter::RequestNormalAttack()
{

	//PtH::Debug() << "APtPlayerCharacter::RequestNormalAttack " << PtH::Endl();
}

void APtPlayerCharacter::SkillOne()
{
	RequestSkill((uint8)ESkillType::Stone);
}

void APtPlayerCharacter::SkillTwo()
{

}

void APtPlayerCharacter::SkillThree()
{

}

void APtPlayerCharacter::SkillFour()
{

}

void APtPlayerCharacter::RequestSkill(uint8 BlockId)
{
	//如果正在操作UI或者已经死亡, 不触发攻击
	if (IsShowBag || HP == 0) {
		return;
	}

	//如果当前被选中的技能框不存在技能, 直接返回
	if (!UPtDataMgr::Get()->IsGoodExit(EBagType::SkillBag, BlockId)) {
		return;
	}		

	//告诉服务器减少物品
	UKBEventData_ReduceGood* EventData = NewObject<UKBEventData_ReduceGood>();
	EventData->BagType = (uint8)EBagType::SkillBag;
	EventData->BlockId = BlockId;
	KBENGINE_EVENT_FIRE("ReduceGood", EventData);
	//PtH::Debug() << "APtPlayerCharacter::RequestAttack: " << BlockId << PtH::Endl();
}

void APtPlayerCharacter::BuffOne()
{
	RequestBuff(0);
}

void APtPlayerCharacter::BuffTwo()
{
	RequestBuff(1);
}

void APtPlayerCharacter::BuffThree()
{
	RequestBuff(2);
}

void APtPlayerCharacter::RequestBuff(uint8 BlockId)
{
	//先判断是否有物品
	if (!UPtDataMgr::Get()->IsGoodExit(EBagType::BuffBag, BlockId)) {
		return;
	}		

	//告诉服务器减少物品
	UKBEventData_ReduceGood* EventData = NewObject<UKBEventData_ReduceGood>();
	EventData->BagType = (uint8)EBagType::BuffBag;
	EventData->BlockId = BlockId;
	KBENGINE_EVENT_FIRE("ReduceGood", EventData);
	PtH::Debug() << "APtPlayerCharacter::RequestBuff: " << BlockId << PtH::Endl();
}


void APtPlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	//修改输入模式,不显示UI
	MainController->SwitchInputMode(false);

	//启动更新动画定时器
	GetWorld()->GetTimerManager().SetTimer(AnimUpdateHandle, this, &APtPlayerCharacter::AnimUpdate, 0.5f, true, 0.5f);
}

void APtPlayerCharacter::Destroyed()
{
	Super::Destroyed();

	//停止定时器
	GetWorld()->GetTimerManager().ClearTimer(AnimUpdateHandle);
}

