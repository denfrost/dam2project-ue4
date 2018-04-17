// Fill out your copyright notice in the Description page of Project Settings.

#include "RespawnVolume.h"
#include "GameCharacter.h"
#include "GameUtils/TeamUtils.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"

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
		Character->OnDeathDelegate.AddUniqueDynamic(this, &ARespawnVolume::ReceiveDeadCharacter);
	}
}

void ARespawnVolume::ReceiveDeadCharacter(AGameCharacter* GameCharacter)
{
	UE_LOG(LogTemp, Warning, TEXT("%s RESPAWN"), *GameCharacter->GetName());
	//GameCharacter->StartSpectatingOnly();
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
	CharacterToRespawn->Dead = false; // TODO remove, respawn testing
	CharacterToRespawn->SetActorLocation(GetActorLocation());
}
