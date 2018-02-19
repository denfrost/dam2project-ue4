// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.generated.h"

/**
 * Extend this class with a Blueprint to define the damage, cooldown
 * and behaviour of an ability executed on a Character, aka
 * PrimaryAbility(), SecondaryAbility(), UltimateAbility()
 * or an Attack from a Weapon. Override ExecuteAbility in the blueprint
 * to define the Ability behaviour.
 */
UCLASS( Blueprintable )
class ARCHITECTURETEST_API AAbility : public AActor
{
	GENERATED_BODY()
	
private:

	UPROPERTY( EditDefaultsOnly )
	int32 Damage;
	
	UPROPERTY( EditDefaultsOnly )
	int32 Cooldown;

	int32 LastUse = 0;

public:

	// TODO podria tener sentido pasarle una referencia al jugador que lanza la ability

	// This defines the behaviour the ability will have if it can be casted
	UFUNCTION(BlueprintImplementableEvent)
	void ExecuteAbility();

	bool InternalExecute();

	bool CanBeExecuted();
};
