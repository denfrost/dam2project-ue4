// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCharacter.h"
#include "ArenaCharacter.generated.h"

class AWeapon;

/**
 * The base class for all characters of the arena battle.
 */
UCLASS( abstract )
class ARCHITECTURETEST_API AArenaCharacter : public AGameCharacter
{
	GENERATED_BODY()

private:

	UPROPERTY( EditAnywhere )
	TSubclassOf<AWeapon> Weapon = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:

	virtual bool PrimaryAbility() override;

	virtual bool SecondaryAbility() override;

	virtual bool UltimateAbility() override;

	bool Respawn() override;

	// Delegate method for Weapon$PrimaryAttack()
	int PrimaryAttack();

	// Delegate method for Weapon$SecondaryAttack()
	int SecondaryAttack();

	// Delegate method for Weapon$Improve()
	int Improve();
};
