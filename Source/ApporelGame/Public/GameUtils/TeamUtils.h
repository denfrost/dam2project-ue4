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

	// TODO add some kinky methods
};

