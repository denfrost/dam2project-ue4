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

	FTimerHandle CooldownTimerHandle;

	bool bHasCooldownEnded;

protected:

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	AAbility();

	/**
	* This defines the behavior the ability will have if it can be casted just by checking its cooldown.
	* If further logic is involved in the implementation, the return value of this method must be used to notify
	* whether the ability could or could not be executed, so the cooldown is updated accordingly.
	*/
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	bool ExecuteAbility(ACharacter* Executor);

	UFUNCTION( BlueprintCallable )
	int32 GetDamage() const;

	UFUNCTION( BlueprintCallable )
	void SetDamage(int32 NewDamage);

	UFUNCTION( BlueprintCallable )
	float GetCooldown() const;

	UFUNCTION( BlueprintCallable )
	FTimerHandle GetCooldownTimerHandle() const;

	UFUNCTION( BlueprintCallable )
	float GetRemainingCooldown() const;

	// Returns the remaining cooldown for this ability as a value between 0.0 and 1.0
	UFUNCTION( BlueprintCallable )
	float GetNormalizedRemainingCooldown() const;

	UFUNCTION( BlueprintCallable )
	void SetCooldown(float NewCooldown);

	UFUNCTION( BlueprintCallable )
	void StartCooldownTimer();

	UFUNCTION( BlueprintCallable )
	void NotifyCooldownEnded();

	virtual bool ExecuteAbility_Implementation(ACharacter* Executor);

	bool InternalExecute(ACharacter* Executor);

	bool HasCooldownEnded() const;
};
