// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "GameUtils/TeamUtils.h"
#include "ApporelGameGameModeBase.generated.h"

UCLASS()
class APPORELGAME_API AApporelGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
protected:
	int32 ScoreTeamBlue = 0.f; // Create Team class (?)
	int32 ScoreTeamRed = 0.f;

	UPROPERTY( EditDefaultsOnly , Category = "Win")
	int32 ScoreToWin = 500.f;

public:
	UFUNCTION(BlueprintCallable)
	int32 GetScore(ETeam Team);

	UFUNCTION(BlueprintCallable)
	void IncrementScore(ETeam Team, int32 Score);

	UFUNCTION(BlueprintCallable)
	void ResetScore(ETeam Team);

	ETeam CheckWinner();

	void NotifyWinner(ETeam Team);

	AApporelGameGameModeBase();

	void BeginPlay();
};
