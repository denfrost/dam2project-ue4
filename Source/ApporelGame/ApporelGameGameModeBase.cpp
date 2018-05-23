// Fill out your copyright notice in the Description page of Project Settings.

#include "ApporelGameGameModeBase.h"
#include "TeamUtils.h"

float AApporelGameGameModeBase::GetScoreTeam(ETeam Team)
{
	return (Team == ETeam::Blue) ? ScoreTeamBlue : ScoreTeamRed;
}

void AApporelGameGameModeBase::IncrementScore(ETeam Team, float Score)
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
