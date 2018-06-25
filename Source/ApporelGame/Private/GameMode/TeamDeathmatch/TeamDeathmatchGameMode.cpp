// Fill out your copyright notice in the Description page of Project Settings.

#include "TeamDeathmatchGameMode.h"
#include "Util/Sounds.h"

ATeamDeathmatchGameMode::ATeamDeathmatchGameMode()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATeamDeathmatchGameMode::BeginPlay()
{
	Super::BeginPlay();

	bIsGameOver = false;
}

int32 ATeamDeathmatchGameMode::GetScore(ETeam Team) const
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

TArray<FPlayerStats> ATeamDeathmatchGameMode::GetSortedPlayerStats() const
{
	TArray<FPlayerStats> PlayerStatsValues;
	PlayerStats.GenerateValueArray(PlayerStatsValues);

	Algo::Sort(PlayerStatsValues, FSortByKDA());

	return PlayerStatsValues;
}

TMap<AGameCharacter*, FPlayerStats> ATeamDeathmatchGameMode::GetPlayerStats() const
{
	return PlayerStats;
}

void ATeamDeathmatchGameMode::IncrementScore(ETeam Team, int32 Score)
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

void ATeamDeathmatchGameMode::ResetScore(ETeam Team)
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

void ATeamDeathmatchGameMode::AnnounceWinnerTeam() const
{
	ETeam Winner = CheckWinner();

	switch (Winner)
	{
	case ETeam::Red:
		USounds::PlaySound2D(GetWorld(), RedTeamWinSound);
		break;

	case ETeam::Blue:
		USounds::PlaySound2D(GetWorld(), BlueTeamWinSound);
		break;

	default:
		break;
	}
}

bool ATeamDeathmatchGameMode::IsGameOver() const
{
	return bIsGameOver;
}

ETeam ATeamDeathmatchGameMode::CheckWinner() const
{
	if (ScoreTeamRed >= ScoreToWin)
		return ETeam::Red;
	else if (ScoreTeamBlue >= ScoreToWin)
		return ETeam::Blue;

	return ETeam::Neutral;
}
