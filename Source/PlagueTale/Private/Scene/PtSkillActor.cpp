// Fill out your copyright notice in the Description page of Project Settings.


#include "PtSkillActor.h"
#include "Particles/ParticleSystemComponent.h"
#include "Engine/World.h"
#include "Components/AudioComponent.h"
#include "PtGameMode.h"
#include "TimerManager.h"

APtSkillActor::APtSkillActor()
{
	PrimaryActorTick.bCanEverTick = true;

	RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootScene"));

	//实例化开火粒子特效组件
	SkillParticleComponent = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("SkillParticleComponent"));
	SkillParticleComponent->SetupAttachment(RootComponent);

	ShootAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ShootAudio"));
	ShootAudio->SetupAttachment(RootComponent);

	ExplodeAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("ExplodeAudio"));
	ExplodeAudio->SetupAttachment(RootComponent);
}

void APtSkillActor::BeginPlay()
{
	Super::BeginPlay();

	if (MainGameMode) {
		MainGameMode->SkillMap.Add(EntityId, this);
	}
	StartSkill();
}

void APtSkillActor::StartSkill()
{
	//一开始就显示技能特效
	SkillParticleComponent->SetTemplate(SkillParticle);

	//播放声音
	ShootAudio->Play();
}

void APtSkillActor::PlayExplode()
{
	//播放爆炸特效
	SkillParticleComponent->SetTemplate(ExplodeParticle);

	//播放声音
	ExplodeAudio->Play();

	//延时1.5秒后销毁
	GetWorld()->GetTimerManager().SetTimer(DestroyHandle, this, &APtSkillActor::DestroySkill, 1.5f);
}

void APtSkillActor::DestroySkill()
{
	Destroy();
}

void APtSkillActor::Destroyed()
{
	Super::Destroyed();

	//从GameMode移除
	if (MainGameMode) {
		MainGameMode->SkillMap.Remove(EntityId);
	}
}
