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
UCLASS( abstract )
class APPORELGAME_API AArenaCharacter : public AGameCharacter
{
	GENERATED_BODY()

private:
	// The character's Weapon (holy fuck man descriptive AF feels like if this shit was created by Epic themselves)
	UPROPERTY( EditAnywhere, Category = "Character Setup")
	TSubclassOf<AWeapon> Weapon = nullptr;

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	UCameraComponent* CameraComp;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USpringArmComponent* SprinArmComp;

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	void MoveForward(float value);

	void MoveRight(float value);

	void BeginCrouch();

	void EndCrouch();
	
public:
	AArenaCharacter();

	const FName GRAB_POINT_SOCKET_NAME = FName("GrabPoint");

	UFUNCTION( BlueprintCallable )
	AWeapon* GetWeapon() const;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	UFUNCTION( BlueprintCallable )
	void SetWeapon(TSubclassOf<AWeapon> NewWeapon);

	// Returns the primary attack of this Character's Weapon
	UFUNCTION( BlueprintCallable )
	AAbility* GetPrimaryAttack() const;

	// Returns the secondary attack of this Character's Weapon
	UFUNCTION( BlueprintCallable )
	AAbility* GetSecondaryAttack() const;

	bool Respawn() override;

	// Delegate method for Weapon$PrimaryAttack()
	void PrimaryAttack();

	// Delegate method for Weapon$SecondaryAttack()
	void SecondaryAttack();

	// Delegate method for Weapon$Improve()
	void Improve();

	/**
	* Override a la funcion de pawn para definir la vista del pawn en la camara y no en la cabeza del pawn.
	*/
	virtual FVector GetPawnViewLocation() const override;
};
