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
	// TODO set events and shit
}

bool AGameCharacter::Respawn()
{
	UE_LOG(LogTemp, Error, TEXT("This is a pure virtual method"));
	return false;
}

bool AGameCharacter::PrimaryAbility()
{
	UE_LOG(LogTemp, Error, TEXT("This is a pure virtual method"));
	return false;
}

bool AGameCharacter::SecondaryAbility()
{
	UE_LOG(LogTemp, Error, TEXT("This is a pure virtual method"));
	return false;
}

bool AGameCharacter::UltimateAbility()
{
	UE_LOG(LogTemp, Error, TEXT("This is a pure virtual method"));
	return false;
}

