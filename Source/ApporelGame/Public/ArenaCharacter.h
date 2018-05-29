// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCharacter.h"
#include "ArenaCharacter.generated.h"

class AWeapon;
class AAbility;
class UCameraComponent;
class USpringArmComponent;

/**
 * The base class for all characters of the arena battle.
 */
UCLASS(abstract)
class APPORELGAME_API AArenaCharacter : public AGameCharacter
{
	GENERATED_BODY()

private:
	// The character's Weapon (holy fuck man descriptive AF feels like if this shit was created by Epic themselves)
	UPROPERTY(EditAnywhere, Category = "Character Setup")
	TSubclassOf<AWeapon> WeaponToSpawn;

	AWeapon* CurrentWeapon;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SprinArmComp;

	void MoveForward(float value);

	void MoveRight(float value);

	void BeginCrouch();

	void EndCrouch();

	virtual void Die() override;

	virtual void RespawnAt(FVector Location) override;

public:
	AArenaCharacter();

	const FName GRAB_POINT_SOCKET_NAME = FName("WeaponSocket");

	UFUNCTION(BlueprintCallable)
	TSubclassOf<AWeapon> GetWeaponToSpawn() const;

	UFUNCTION(BlueprintCallable)
	void SetWeaponToSpawn(TSubclassOf<AWeapon> NewWeapon);

	UFUNCTION(BlueprintCallable)
	AWeapon* GetCurrentWeapon();

	UFUNCTION(BlueprintCallable)
	void SetCurrentWeapon(AWeapon* NewCurrentWeapon);

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Returns the primary attack of this Character's Weapon
	UFUNCTION(BlueprintCallable)
	AAbility* GetPrimaryAttack() const;

	// Returns the secondary attack of this Character's Weapon
	UFUNCTION(BlueprintCallable)
	AAbility* GetSecondaryAttack() const;

	// Delegate method for Weapon$StartPrimaryAttack()
	void StartPrimaryAttack();

	// Delegate method for Weapon$StopPrimaryAttack()
	void StopPrimaryAttack();

	// Delegate method for Weapon$SecondaryAttack()
	void SecondaryAttack();

	// Delegate method for Weapon$Improve()
	void Improve();

	// Pawn function override to define the character's view point on the camera instead of on the pawn's head
	virtual FVector GetPawnViewLocation() const override;
};
