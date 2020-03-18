// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PtBaseCharacter.h"
#include "PtRemotePlayerCharacter.generated.h"

class UBoxComponent;

/**
 * 
 */
UCLASS()
class PLAGUETALE_API APtRemotePlayerCharacter : public APtBaseCharacter
{
	GENERATED_BODY()

public:
	APtRemotePlayerCharacter();

	virtual void Tick(float DeltaTime) override;

	virtual void SetBaseHP(int32 InBaseHP) override;

	virtual void SetHP(int32 InHP) override;

	/**	攻击回调，实现具体的攻击表现 */
	virtual void OnAttack(uint8 SkillID)override;

protected:
	virtual void BeginPlay() override;

	/**	用于更新动画的检测跳跃 */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	/**	判断是否着地碰撞体 */
	UPROPERTY(EditAnywhere)
	UBoxComponent* GroundBox;

	UPROPERTY(EditAnywhere)
	class UWidgetComponent* BloodBarComponent;

protected:
	/**	地面名称，这里直接与地图里的地面mesh名称要相同，也就是地面mesh取名为"Ground" ，
		同时要开始地面MeshActor的GenerateOverlapEvents */
	static FName GroundName;

	class UPtBloodBar* BloodBar;
};
