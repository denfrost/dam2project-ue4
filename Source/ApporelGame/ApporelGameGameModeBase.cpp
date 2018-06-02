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
}

int32 AApporelGameGameModeBase::GetScore(ETeam Team)
{
	return (Team == ETeam::Blue) ? ScoreTeamBlue : ScoreTeamRed;
}

TMap<AGameCharacter*, FPlayerStats> AApporelGameGameModeBase::GetPlayerStats() const
{
	return PlayerStats;
}

void AApporelGameGameModeBase::IncrementScore(ETeam Team, int32 Score)
{
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
		NotifyWinner(Winner);
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

ETeam AApporelGameGameModeBase::CheckWinner()
{
	if (ScoreTeamRed >= ScoreToWin)
		return ETeam::Red;
	else if (ScoreTeamBlue >= ScoreToWin)
		return ETeam::Blue;

	return ETeam::Neutral;
}

void AApporelGameGameModeBase::NotifyWinner(ETeam Team)
{
	FString WinnerName = Team == ETeam::Blue ? "Blue" : "Red";

	UE_LOG(LogTemp, Warning, TEXT("Winner : %s"), *WinnerName);
}
