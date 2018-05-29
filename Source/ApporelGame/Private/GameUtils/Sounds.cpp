// Fill out your copyright notice in the Description page of Project Settings.

#include "Sounds.h"
#include "Kismet/GameplayStatics.h"


void USounds::PlaySound2D(UWorld* WorldContext, USoundBase* Sound)
{
	if (!Sound)
	{
		UE_LOG(LogTemp, Warning, TEXT("USounds::PlaySound2D could not play the sound because it was nullptr"));
		return;
	}
	UGameplayStatics::PlaySound2D(WorldContext, Sound);
}

void USounds::PlayRandomSound2D(UWorld* WorldContext, TArray<USoundBase*> Sounds)
{
	if (Sounds.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("USounds::PlayRandomSound2D could not play any sound because it received an empty array"));
		return;
	}
	auto RandomIndex = FMath::RandRange(0, Sounds.Num() - 1);
	UGameplayStatics::PlaySound2D(WorldContext, Sounds[RandomIndex]);
}

void USounds::PlaySoundAtLocation(UWorld* WorldContext, USoundBase* Sound, FVector Location)
{
	if (!Sound)
	{
		UE_LOG(LogTemp, Warning, TEXT("USounds::PlaySoundAtLocation could not play the sound because it was nullptr"));
		return;
	}
	UGameplayStatics::PlaySoundAtLocation(WorldContext, Sound, Location);
}

void USounds::PlayRandomSoundAtLocation(UWorld* WorldContext, TArray<USoundBase*> Sounds, FVector Location)
{
	if (Sounds.Num() == 0)
	{
		UE_LOG(LogTemp, Warning, TEXT("USounds::PlayRandomSoundAtLocation could not play any sound because it received an empty array"));
		return;
	}
	auto RandomIndex = FMath::RandRange(0, Sounds.Num() - 1);
	UGameplayStatics::PlaySoundAtLocation(WorldContext, Sounds[RandomIndex], Location);
}
