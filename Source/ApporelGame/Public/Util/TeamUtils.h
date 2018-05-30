// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "TeamUtils.generated.h"

UENUM(BlueprintType)
enum class ETeam : uint8
{
	Red			UMETA(DisplayName = "Red Team"),
	Blue		UMETA(DisplayName = "Blue Team"),
	Neutral		UMETA(DisplayName = "Neutral")
};

/**
* Class containing diverse utility methods for Teams
*/
UCLASS()
class APPORELGAME_API UTeamUtils : public UObject
{
	GENERATED_BODY()

public:

	// Returns an array of all spawned actors of a class T
	template<typename T>
	UFUNCTION( BlueprintCallable )
	static void FindAllActors(UWorld* WorldContext, TArray<T*>& Out);

	// Returns all the spawned game characters from a given team
	UFUNCTION( BlueprintCallable )
	static TArray<class AGameCharacter*> FindCharactersFromTeam(UWorld* WorldContext, ETeam Team);
};
