// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayerController.h"
#include "GameCharacter.h"

ETeam AGamePlayerController::GetTeam() const
{
	return Team;
}

void AGamePlayerController::SetTeam(ETeam NewTeam)
{
	Team = NewTeam;
}

bool AGamePlayerController::IsControlledPawnDead()
{
	auto ControlledCharacter = Cast<AGameCharacter>(GetPawn());
	return ControlledCharacter->IsDead();
}
