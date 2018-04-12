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
UCLASS(abstract)
class APPORELGAME_API UTeamUtils : public UObject
{
	GENERATED_BODY()

	// Set this to a valid world right after creation
	UPROPERTY(Transient)
	UWorld* World;

	// Begin UObject interface
	virtual class UWorld* GetWorld() const override;

	// Returns all the game characters from a given team
	//TArray<class AGameCharacter*> GetCharactersFromTeam(ETeam Team);
};
