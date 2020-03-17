// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Scene/PtActorEntity.h"
#include "PtFlobActor.generated.h"


class UStaticMeshComponent;
class UMaterialInterface;
class UMaterialInstanceDynamic;

/**
 * 可拾取的掉落物
 */
UCLASS()
class PLAGUETALE_API APtFlobActor : public APtActorEntity
{
	GENERATED_BODY()
public:

	APtFlobActor();

	virtual void Tick(float DeltaTime) override;

	virtual void Destroyed() override;

public:

	UPROPERTY(EditAnywhere)
	UStaticMeshComponent* BaseMesh;

	UPROPERTY(EditAnywhere)
	UMaterialInterface* BaseMat;

	UPROPERTY()
	UMaterialInstanceDynamic* BaseMatInst;

	uint8 GoodId;

protected:

	virtual void BeginPlay() override;
};
