// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCharacter.h"

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AGameCharacter::OnDeath()
{

}

bool AGameCharacter::Respawn()
{
	return false;
}

bool AGameCharacter::PrimaryAbility()
{
	return false;
}

bool AGameCharacter::SecondaryAbility()
{
	return false;
}

bool AGameCharacter::UltimateAbility()
{
	return false;
}

