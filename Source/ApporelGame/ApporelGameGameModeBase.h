// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "ApporelGameGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class APPORELGAME_API AApporelGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	float ScoreTeamBlue = 0.f; // Create Team class (?)
	float ScoreTeamRed = 0.f; 

public:
	UFUNCTION(BlueprintCallable)
	float GetScoreTeam(ETeam Team);

	UFUNCTION(BlueprintCallable)
	void IncrementScore(ETeam Team, float Score);

	UFUNCTION(BlueprintCallable)
	void ResetScore(ETeam Team);
};
