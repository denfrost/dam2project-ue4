// Fill out your copyright notice in the Description page of Project Settings.
#define OUT

#include "GameCharacter.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"
#include "TeamUtils.h"

UWorld* UTeamUtils::GetWorld() const
{
	return World;
}

template<typename T>
void UTeamUtils::FindAllActors(UWorld* World, TArray<T*>& Out)
{
	for (TActorIterator<AActor> It(World, T::StaticClass()); It; ++It)
	{
		T* Actor = Cast<T>(*It);
		if (Actor && !Actor->IsPendingKill())
		{
			Out.Add(Actor);
		}
	}
}

TArray<class AGameCharacter*> UTeamUtils::FindCharactersFromTeam(ETeam Team)
{
	TArray<AGameCharacter*>		CharactersFromTeam;
	TArray<AGameCharacter*>		Characters;
	FindAllActors( GetWorld(), OUT Characters );

	for (AGameCharacter* Character : Characters)
	{
		if (Character->GetTeam() == Team)
		{
			CharactersFromTeam.Add(Character);
		}
	}
	return CharactersFromTeam;
}
