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

protected:
	/**	用于更新动画的检测跳跃 */
	UFUNCTION()
	void OnOverlapBegin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	UFUNCTION()
	void OnOverlapEnd(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);
public:
	/**	判断是否着地碰撞体 */
	UPROPERTY(EditAnywhere)
	UBoxComponent* GroundBox;

protected:
	/**	地面名称，这里直接与地图里的地面mesh名称要相同，也就是地面mesh取名为"Ground" ，
		同时要开始地面MeshActor的GenerateOverlapEvents */
	static FName GroundName;

};
