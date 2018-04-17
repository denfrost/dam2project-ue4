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

private:

	// Set this to a valid world right after creation
	UPROPERTY(Transient)
	UWorld* World;

	// UObject interface
	virtual class UWorld* GetWorld() const override;

public:

	// Returns an array of all spawned actors of a class T
	template<typename T>
	void FindAllActors(UWorld* World, TArray<T*>& Out);

	// Returns all the spawned game characters from a given team
	TArray<class AGameCharacter*> FindCharactersFromTeam(UWorld* World, ETeam Team);
};
