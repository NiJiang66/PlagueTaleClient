// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PtKBEClient.generated.h"

class UKBEMain;

/**
 *	KBE客户端入口类，用于承载KBEMain组件的Actor
 */
UCLASS()
class PLAGUETALE_API APtKBEClient : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	APtKBEClient();


public:
	UPROPERTY(EditAnywhere)
	UKBEMain* KBEMain;

};
