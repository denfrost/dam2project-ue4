// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCharacter.h"
#include "ArenaCharacter.generated.h"

/**
 * 
 */
UCLASS( abstract )
class ARCHITECTURETEST_API AArenaCharacter : public AGameCharacter
{
	GENERATED_BODY()
	
	
public:
	bool Respawn() override;

	virtual bool PrimaryAbility() override;

	virtual bool SecondaryAbility() override;

	virtual bool UltimateAbility() override;
};
