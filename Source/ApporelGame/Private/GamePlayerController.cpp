// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayerController.h"
#include "GameCharacter.h"

bool AGamePlayerController::IsControlledPawnDead()
{
	auto ControlledCharacter = Cast<AGameCharacter>(GetPawn());
	return ControlledCharacter->IsDead();
}
