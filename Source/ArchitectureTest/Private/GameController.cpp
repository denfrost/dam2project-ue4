// Fill out your copyright notice in the Description page of Project Settings.

#include "GameController.h"
#include "GameplayTagContainer.h"

ETeam AGameController::GetTeam()
{
	return Team;
}

void AGameController::SetTeam(ETeam NewTeam)
{
	Team = NewTeam;
}