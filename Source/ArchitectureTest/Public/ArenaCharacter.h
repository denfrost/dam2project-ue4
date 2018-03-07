// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameCharacter.h"
#include "ArenaCharacter.generated.h"

class AWeapon;
class AAbility;

/**
 * The base class for all characters of the arena battle.
 */
UCLASS( abstract )
class ARCHITECTURETEST_API AArenaCharacter : public AGameCharacter
{
	GENERATED_BODY()

private:
	// The character's Weapon (holy fuck man descriptive AF feels like if this shit was created by Epic themselves)
	UPROPERTY( EditAnywhere, Category = "Character Setup")
	TSubclassOf<AWeapon> Weapon = nullptr;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	FName GRAB_POINT_SOCKET_NAME = FName("GrabPoint");

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION( BlueprintCallable )
	AWeapon* GetWeapon();

	UFUNCTION( BlueprintCallable )
	void SetWeapon(TSubclassOf<AWeapon> NewWeapon);

	// Returns the primary attack of this Character's Weapon
	UFUNCTION( BlueprintCallable )
	AAbility* GetPrimaryAttack();

	// Returns the secondary attack of this Character's Weapon
	UFUNCTION( BlueprintCallable )
	AAbility* GetSecondaryAttack();

	bool Respawn() override;

	// Delegate method for Weapon$PrimaryAttack()
	void PrimaryAttack();

	// Delegate method for Weapon$SecondaryAttack()
	void SecondaryAttack();

	// Delegate method for Weapon$Improve()
	void Improve();
};
