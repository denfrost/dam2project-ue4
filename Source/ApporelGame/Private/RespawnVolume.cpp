// Fill out your copyright notice in the Description page of Project Settings.

#include "RespawnVolume.h"
#include "GameCharacter.h"
#include "Util/TeamUtils.h"
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

void ARespawnVolume::ReceiveDeadCharacter_Implementation(AGameCharacter* Dead, AGameCharacter* Killer)
{
	CharactersToRespawn.Enqueue(Dead);

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

//bool ARespawnVolume::ReceiveDeadCharacter_Validate(AGameCharacter* Dead, AGameCharacter* Killer)
//{
//	return true;
//}

void ARespawnVolume::RespawnCharacter_Implementation()
{
	AGameCharacter* CharacterToRespawn;
	CharactersToRespawn.Dequeue(CharacterToRespawn);
	CharacterToRespawn->RespawnAt(GetActorLocation());
}

//bool ARespawnVolume::RespawnCharacter_Validate()
//{
//	return true;
//}