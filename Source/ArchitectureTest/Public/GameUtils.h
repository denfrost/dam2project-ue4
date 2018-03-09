// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "GameUtils.generated.h"

UENUM( BlueprintType )
enum class ETeam : uint8
{
	Red			UMETA(DisplayName = "Red Team"),
	Blue		UMETA(DisplayName = "Blue Team"),
	Neutral		UMETA(DisplayName = "Neutral")
};

/**
 * Class containing various utilities for the game as the Team enum, methods for querying it, etc.
 */
UCLASS( abstract )
class ARCHITECTURETEST_API UGameUtils : public UObject
{
	GENERATED_BODY()
};
