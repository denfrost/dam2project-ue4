// Fill out your copyright notice in the Description page of Project Settings.

#include "GameController.h"

ETeam AGameController::GetTeam() const
{
	return Team;
}

void AGameController::SetTeam(ETeam NewTeam)
{
	Team = NewTeam;
}
