// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaCharacter.h"
#include "Weapon.h"
#include "Ability.h"

void AArenaCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AArenaCharacter::PrimaryAttack);
	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &AArenaCharacter::SecondaryAttack);
}

AWeapon* AArenaCharacter::GetWeapon()
{
	ensure(Weapon != nullptr);
	return Weapon.GetDefaultObject();
}

void AArenaCharacter::SetWeapon(TSubclassOf<AWeapon> NewWeapon)
{
	Weapon = NewWeapon;
	NewWeapon.GetDefaultObject()->SetOwningCharacter(this);
}

AAbility* AArenaCharacter::GetPrimaryAttack()
{
	ensure(Weapon != nullptr);
	return GetWeapon()->GetPrimaryAttack();
}

AAbility* AArenaCharacter::GetSecondaryAttack()
{
	ensure(Weapon != nullptr);
	return GetWeapon()->GetSecondaryAttack();
}

// Called when the game starts or when spawned
void AArenaCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (Weapon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a weapon!"), *GetName());
		return;
	}
	SetWeapon(Weapon); // To call Weapon->SetOwningCharacter(this)

	// Set Weapon attacks last use to -Cooldown to be able to cast them instantly at the beginning of the match
	GetWeapon()->GetPrimaryAttack()->SetLastUse(-GetWeapon()->GetPrimaryAttack()->GetCooldown());
	GetWeapon()->GetSecondaryAttack()->SetLastUse(-GetWeapon()->GetSecondaryAttack()->GetCooldown());

	// Spawn the Weapon and attach it to the player
	auto Spawned = GetWorld()->SpawnActor(GetWeapon()->GetClass());
	Spawned->AttachToActor(this, FAttachmentTransformRules::KeepRelativeTransform, GRAB_POINT_SOCKET_NAME);
}

bool AArenaCharacter::Respawn()
{
	// TODO implement
	return false;
}

void AArenaCharacter::PrimaryAttack()
{
	if (Weapon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a weapon!"), *GetName());
		return;
	}
	return Weapon.GetDefaultObject()->ExecutePrimaryAttack();
}

void AArenaCharacter::SecondaryAttack()
{
	if (Weapon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a weapon!"), *GetName());
		return;
	}
	return Weapon.GetDefaultObject()->ExecuteSecondaryAttack();
}

void AArenaCharacter::Improve()
{
	return Weapon.GetDefaultObject()->ExecuteImprove();
}