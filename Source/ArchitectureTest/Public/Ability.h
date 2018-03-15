// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Ability.generated.h"

/**
 * Extend this class with a Blueprint to define the damage, cooldown
 * and behavior of an ability executed on a Character, aka
 * PrimaryAbility(), SecondaryAbility(), UltimateAbility()
 * or an Attack from a Weapon. Override ExecuteAbility in the Ability BP
 * to define the Ability behavior.
 */
UCLASS( Blueprintable )
class ARCHITECTURETEST_API AAbility : public AActor
{
	GENERATED_BODY()
	
private:

	// The damage caused by this Ability
	UPROPERTY( EditDefaultsOnly )
	int32 Damage;
	
	// The cooldown of this Ability. Note that the cooldown is managed internally so you don't have to worry about it in the behavior implementation
	UPROPERTY( EditDefaultsOnly )
	float Cooldown;

	float LastUse;

public:

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION( BlueprintCallable )
	int32 GetDamage() const;

	UFUNCTION( BlueprintCallable )
	void SetDamage(int32 NewDamage);

	UFUNCTION( BlueprintCallable )
	float GetCooldown() const;

	UFUNCTION( BlueprintCallable )
	void SetCooldown(float NewCooldown);

	UFUNCTION( BlueprintCallable )
	float GetLastUse() const;

	void SetLastUse(float NewLastUse);

	// This defines the behavior the ability will have if it can be casted
	UFUNCTION( BlueprintImplementableEvent )
	void ExecuteAbility(AActor* executor);

	void InternalExecute(AActor* executor);

	bool CanBeExecuted(const AActor* executor);
};
