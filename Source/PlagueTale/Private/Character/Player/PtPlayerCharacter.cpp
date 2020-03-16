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

