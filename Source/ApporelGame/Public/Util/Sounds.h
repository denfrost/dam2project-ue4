// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Sounds.generated.h"

/**
 * 
 */
UCLASS()
class APPORELGAME_API USounds : public UObject
{
	GENERATED_BODY()
	
public:
	
	// Plays the specified Sound directly without attenuation
	UFUNCTION( BlueprintCallable )
	static void PlaySound2D(UWorld* WorldContext, USoundBase* Sound);

	// Plays a random Sound directly without attenuation from the given array
	UFUNCTION( BlueprintCallable )
	static void PlayRandomSound2D(UWorld* WorldContext, TArray<USoundBase*> Sounds);

	// Plays the specified Sound at the given Location.
	UFUNCTION( BlueprintCallable )
	static void PlaySoundAtLocation(UWorld* WorldContext, USoundBase* Sound, FVector Location);

	// Plays a random Sound from the given array at the specified Location.
	UFUNCTION( BlueprintCallable )
	static void PlayRandomSoundAtLocation(UWorld* WorldContext, TArray<USoundBase*> Sounds, FVector Location);
};
