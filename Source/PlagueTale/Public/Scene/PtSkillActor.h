// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/PtActorEntity.h"
#include "PtSkillActor.generated.h"


class UParticleSystemComponent;
class UParticleSystem;
class UAudioComponent;

/**
 * 技能Actor
 */
UCLASS()
class PLAGUETALE_API APtSkillActor : public APtActorEntity
{
	GENERATED_BODY()
public:

	APtSkillActor();

	virtual void Destroyed() override;

	/**	播放开始技能特效 */
	virtual void StartSkill();

	/**	服务端销毁, 播放爆炸特效 */
	virtual void PlayExplode();

protected:
	/**	销毁技能 */
	void DestroySkill();

	virtual void BeginPlay() override;

protected:
	/**	计时器 */
	FTimerHandle DestroyHandle;

public:
	/**	技能id */
	uint8 SkillId;

	/**	特效组件 */
	UPROPERTY(EditAnywhere)
	UParticleSystemComponent* SkillParticleComponent;
	/**	技能特效 */
	UPROPERTY(EditAnywhere)
	UParticleSystem* SkillParticle;
	/**	爆炸特效 */
	UPROPERTY(EditAnywhere)
	UParticleSystem* ExplodeParticle;

	UPROPERTY(EditAnywhere)
	UAudioComponent* ShootAudio;
	UPROPERTY(EditAnywhere)
	UAudioComponent* ExplodeAudio;
};
