// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.generated.h"

class ACharacter;

/**
 * Extend this class with a Blueprint to define the damage, cooldown
 * and behavior of an ability executed on a Character, aka
 * PrimaryAbility(), SecondaryAbility(), UltimateAbility()
 * or an Attack from a Weapon. Override ExecuteAbility in the Ability BP
 * to define the Ability behavior.
 */
UCLASS( Blueprintable )
class APPORELGAME_API AAbility : public AActor
{
	GENERATED_BODY()
	
private:

	// The damage caused by this Ability
	UPROPERTY( EditDefaultsOnly )
	int32 Damage;
	
	// The cooldown of this Ability. Note that the cooldown is managed internally so you don't have to worry about it in the behavior implementation
	UPROPERTY( EditDefaultsOnly )
	float Cooldown;

	// The sound this Ability will emit when successfully executed
	UPROPERTY( EditDefaultsOnly )
	USoundBase* Sound;

	float LastUse;

	bool bCouldBlueprintExecute;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

	UFUNCTION( BlueprintCallable )
	int32 GetDamage() const;

	UFUNCTION( BlueprintCallable )
	void SetDamage(int32 NewDamage);

	UFUNCTION( BlueprintCallable )
	float GetCooldown() const;

	// Returns the remaining cooldown for this ability as a value between 0.0 and 1.0
	UFUNCTION( BlueprintCallable )
	float GetNormalizedRemainingCooldown() const;

	UFUNCTION( BlueprintCallable )
	void SetCooldown(float NewCooldown);

	UFUNCTION( BlueprintCallable )
	float GetLastUse() const;

	void SetLastUse(float NewLastUse);

	// This defines the behavior the ability will have if it can be casted
	UFUNCTION( BlueprintNativeEvent )
	bool ExecuteAbility(ACharacter* executor);

	virtual bool ExecuteAbility_Implementation(ACharacter* executor);

	// This function must be called if the ability couldn't be executed because of the BP logic
	UFUNCTION( BlueprintCallable )
	void NotifyBlueprintCouldNotExecute();

	bool InternalExecute(ACharacter* executor);

	bool CanBeExecuted(const ACharacter* executor) const;
};
