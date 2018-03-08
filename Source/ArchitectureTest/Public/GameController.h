// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Controller.h"
#include "GameController.generated.h"

UENUM( BlueprintType )
enum class ETeam : uint8
{
	Red		UMETA( DisplayName="Red Team" ),
	Blue	UMETA( DisplayName="Blue Team" )
	// TODO implementar Neutral y mover a otra clase para utilizarlo en CapturableVolume
};

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
