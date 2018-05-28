// Fill out your copyright notice in the Description page of Project Settings.

#include "GameController.h"
#include "GameCharacter.h"

ETeam AGameController::GetTeam() const
{
	return Team;
}

void AGameController::SetTeam(ETeam NewTeam)
{
	Team = NewTeam;
}

bool AGameController::IsControlledPawnDead()
{
	auto ControlledCharacter = Cast<AGameCharacter>(GetPawn());
	return ControlledCharacter->IsDead();
}
