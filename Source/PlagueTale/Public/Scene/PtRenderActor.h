// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PtRenderActor.generated.h"


/**
 *	渲染角色到RenderTexture的场景Actor
 */
UCLASS()
class PLAGUETALE_API APtRenderActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APtRenderActor();

	/**
	 * 切换角色模型
	 * @pram	RoleType	角色类型		
	 */
	UFUNCTION(BlueprintImplementableEvent)
	void SwitchRoleMesh(uint8 RoleType);

};
