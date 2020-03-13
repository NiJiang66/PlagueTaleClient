// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Character/PTBaseCharacter.h"
#include "PtPlayerCharacter.generated.h"

/**
 * 
 */
UCLASS()
class PLAGUETALE_API APtPlayerCharacter : public APtBaseCharacter
{
	GENERATED_BODY()
		
public:

	APtPlayerCharacter();

public:

	class UCameraComponent* CameraComponent = nullptr;
};
