// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUtils.h"
#include "GameFramework/Controller.h"
#include "GameController.generated.h"

/**
 * 
 */
UCLASS( Blueprintable )
class ARCHITECTURETEST_API AGameController : public AController
{
	GENERATED_BODY()

private:
	UPROPERTY( EditAnywhere )
	ETeam Team;

public:
	UFUNCTION( BlueprintCallable )
	ETeam GetTeam();

	UFUNCTION( BlueprintCallable )
	void SetTeam(ETeam NewTeam);
	
};
