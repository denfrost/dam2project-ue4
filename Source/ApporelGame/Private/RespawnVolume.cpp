// Fill out your copyright notice in the Description page of Project Settings.

#include "RespawnVolume.h"
#include "GameCharacter.h"
#include "GameUtils/TeamUtils.h"

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

	UTeamUtils* TeamUtils = NewObject<UTeamUtils>();
	TArray<AGameCharacter*> Characters = TeamUtils->FindCharactersFromTeam(GetWorld(), Team);

	for (AGameCharacter* Character : Characters)
	{
		Character->OnDeathDelegate.AddUniqueDynamic(this, &ARespawnVolume::Respawn);
	}
}

void ARespawnVolume::Respawn(AGameCharacter* GameCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("%s RESPAWN"), *GameCharacter->GetName());
	// TODO
	// invalidate dead player
	// start a timer with TimeToRespawn
	// on timer finish teleport dead player to a random point of the volume
}
