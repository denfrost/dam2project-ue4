// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "GamePlayerController.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class APPORELGAME_API AGamePlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	UFUNCTION( BlueprintCallable )
	bool IsControlledPawnDead();
	
};
