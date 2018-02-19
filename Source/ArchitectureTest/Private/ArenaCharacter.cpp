// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaCharacter.h"
#include "Weapon.h"

// Called when the game starts or when spawned
void AArenaCharacter::BeginPlay()
{
	Super::BeginPlay();
	ensure(Weapon != nullptr);
}

bool AArenaCharacter::Respawn()
{
	// TODO implement
	return false;
}

int AArenaCharacter::PrimaryAttack()
{
	return Weapon.GetDefaultObject()->PrimaryAttack();
}

int AArenaCharacter::SecondaryAttack()
{
	return Weapon.GetDefaultObject()->SecondaryAttack();
}

int AArenaCharacter::Improve()
{
	return Weapon.GetDefaultObject()->Improve();
}

bool AArenaCharacter::PrimaryAbility()
{
	UE_LOG(LogTemp, Error, TEXT("This is a pure virtual method"));
	return false;
}

bool AArenaCharacter::SecondaryAbility()
{
	UE_LOG(LogTemp, Error, TEXT("This is a pure virtual method"));
	return false;
}

bool AArenaCharacter::UltimateAbility()
{
	UE_LOG(LogTemp, Error, TEXT("This is a pure virtual method"));
	return false;
}