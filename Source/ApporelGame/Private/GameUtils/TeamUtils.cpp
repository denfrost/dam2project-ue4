// Fill out your copyright notice in the Description page of Project Settings.
#include "TeamUtils.h"
#include "GameCharacter.h"
#include "Runtime/Engine/Public/EngineUtils.h"
#include "Runtime/Engine/Classes/GameFramework/Actor.h"

#define OUT

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

TArray<class AGameCharacter*> UTeamUtils::FindCharactersFromTeam(UWorld* World, ETeam Team)
{
	TArray<AGameCharacter*>		CharactersFromTeam;
	TArray<AGameCharacter*>		Characters;
	FindAllActors( World, OUT Characters );

	for (AGameCharacter* Character : Characters)
	{
		if (Character->GetTeam() == Team)
		{
			CharactersFromTeam.Add(Character);
		}
	}
	return CharactersFromTeam;
}
