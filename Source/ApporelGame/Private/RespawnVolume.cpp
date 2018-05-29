// Fill out your copyright notice in the Description page of Project Settings.

#include "RespawnVolume.h"
#include "GameCharacter.h"
#include "GameUtils/TeamUtils.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"

#define OUT

// Sets default values
ARespawnVolume::ARespawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ARespawnVolume::BeginPlay()
{
	Super::BeginPlay();

	TArray<AGameCharacter*> Characters = UTeamUtils::FindCharactersFromTeam(GetWorld(), Team);

	for (AGameCharacter* Character : Characters)
	{
		Character->OnDeathDelegate.AddUniqueDynamic(this, &ARespawnVolume::ReceiveDeadCharacter);
	}
}

void ARespawnVolume::ReceiveDeadCharacter(AGameCharacter* GameCharacter)
{
	CharactersToRespawn.Add(GameCharacter);

	FTimerHandle TimerHandle;
	GetWorldTimerManager().SetTimer
	(
		TimerHandle,
		this,
		&ARespawnVolume::RespawnCharacter,
		TimeToRespawn,
		false
	);
}

void ARespawnVolume::RespawnCharacter()
{
	auto CharacterToRespawn = CharactersToRespawn.Pop();
	CharacterToRespawn->RespawnAt(GetActorLocation());
}
