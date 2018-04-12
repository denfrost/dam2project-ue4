// Fill out your copyright notice in the Description page of Project Settings.

#include "RespawnVolume.h"

#define OUT

// Sets default values
ARespawnVolume::ARespawnVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

void ARespawnVolume::BeginPlay()
{
	Super::BeginPlay();

	// TODO
	// get all players from team (this respawn team)
	// for each player
		// add the respawn as OnDeath listener
}

void ARespawnVolume::Respawn(class AGameCharacter* GameCharacter)
{
	// TODO
	// invalidate dead player
	// start a timer with TimeToRespawn
	// on timer finish teleport dead player to a random point of the volume
}
