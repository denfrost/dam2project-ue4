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

	UPROPERTY( EditAnywhere, Category = "Character Setup")
	TSubclassOf<AWeapon> Weapon = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:

	bool Respawn() override;

	// TODO change methods for Ability calls

	// Delegate method for Weapon$PrimaryAttack()
	int PrimaryAttack();

	// Delegate method for Weapon$SecondaryAttack()
	int SecondaryAttack();

	// Delegate method for Weapon$Improve()
	int Improve();
};
