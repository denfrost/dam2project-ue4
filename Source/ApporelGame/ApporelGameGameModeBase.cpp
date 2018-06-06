// Fill out your copyright notice in the Description page of Project Settings.

#include "ApporelGameGameModeBase.h"
#include "TeamUtils.h"

AApporelGameGameModeBase::AApporelGameGameModeBase()
{
	PrimaryActorTick.bCanEverTick = false;
}

void AApporelGameGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	bIsGameOver = false;
}

int32 AApporelGameGameModeBase::GetScore(ETeam Team) const
{
	return (Team == ETeam::Blue) ? ScoreTeamBlue : ScoreTeamRed;
}

struct FSortByKDA
{
	bool operator()(const FPlayerStats A, const FPlayerStats B) const
	{
		return ( (A.Kills + 1) / (float)(A.Deaths + 1) ) > ( (B.Kills + 1) / (float)(B.Deaths + 1) );
	}
};

TArray<FPlayerStats> AApporelGameGameModeBase::GetSortedPlayerStats() const
{
	TArray<FPlayerStats> PlayerStatsValues;
	PlayerStats.GenerateValueArray(PlayerStatsValues);

	Algo::Sort(PlayerStatsValues, FSortByKDA());

	return PlayerStatsValues;
}

TMap<AGameCharacter*, FPlayerStats> AApporelGameGameModeBase::GetPlayerStats() const
{
	return PlayerStats;
}

void AApporelGameGameModeBase::IncrementScore(ETeam Team, int32 Score)
{
	if (bIsGameOver)
	{
		return;
	}

	switch (Team)
	{
	case ETeam::Blue:
		ScoreTeamBlue += Score;
		break;
	case ETeam::Red:
		ScoreTeamRed += Score;
		break;
	default:
		break;
	}

	ETeam Winner = CheckWinner();
	if (Winner != ETeam::Neutral)
	{
		bIsGameOver = true;
		OnGameOver(Winner);
	}
}

void AApporelGameGameModeBase::ResetScore(ETeam Team)
{
	switch (Team)
	{
	case ETeam::Blue:
		ScoreTeamBlue = 0;
		break;
	case ETeam::Red:
		ScoreTeamRed = 0;
		break;
	default:
		break;
	}
}

bool AApporelGameGameModeBase::IsGameOver() const
{
	return bIsGameOver;
}

ETeam AApporelGameGameModeBase::CheckWinner() const
{
	if (ScoreTeamRed >= ScoreToWin)
		return ETeam::Red;
	else if (ScoreTeamBlue >= ScoreToWin)
		return ETeam::Blue;

	return ETeam::Neutral;
}
