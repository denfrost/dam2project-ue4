// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.generated.h"

/**
 * Extend this class with a Blueprint to define the damage, cooldown
 * and behaviour of an ability executed on a Character, aka
 * PrimaryAbility(), SecondaryAbility(), UltimateAbility()
 * or an Attack from a Weapon. Override ExecuteAbility in the Ability BP
 * to define the Ability behaviour.
 */
UCLASS( Blueprintable )
class ARCHITECTURETEST_API AAbility : public AActor
{
	GENERATED_BODY()
	
private:

	// The damage caused by this Ability
	UPROPERTY( EditDefaultsOnly )
	int32 Damage;
	
	// The cooldown of this Ability. Note that the cooldown is managed internally so you don't have to worry about it in the behaviour implementation
	UPROPERTY( EditDefaultsOnly )
	float Cooldown;

	float LastUse = 0.f;

public:

	UFUNCTION( BlueprintCallable )
	int32 GetDamage();

	UFUNCTION( BlueprintCallable )
	void SetDamage(int32 NewDamage);

	UFUNCTION( BlueprintCallable )
	float GetCooldown();

	UFUNCTION( BlueprintCallable )
	void SetCooldown(float NewCooldown);

	// This defines the behaviour the ability will have if it can be casted
	UFUNCTION(BlueprintImplementableEvent)
	void ExecuteAbility(AActor* executor);

	void InternalExecute(AActor* executor);

	bool CanBeExecuted(const AActor* executor);
};
