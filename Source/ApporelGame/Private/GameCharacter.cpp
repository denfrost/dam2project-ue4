// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCharacter.h"
#include "GameController.h"
#include "Ability.h"

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PrimaryAbility == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a primary ability!"), *GetName());
	}

	if (SecondaryAbility == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a secondary ability!"), *GetName());
	}

	if (UltimateAbility == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have an ultimate ability!"), *GetName());
	}

	// Set Abilities last use to -Cooldown to be able to cast them instantly at the beginning of the match
	PrimaryAbility.GetDefaultObject()->SetLastUse(-PrimaryAbility.GetDefaultObject()->GetCooldown());
	SecondaryAbility.GetDefaultObject()->SetLastUse(-SecondaryAbility.GetDefaultObject()->GetCooldown());
	UltimateAbility.GetDefaultObject()->SetLastUse(-UltimateAbility.GetDefaultObject()->GetCooldown());
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
	PlayerInputComponent->BindAction("PrimaryAbility", IE_Pressed, this, &AGameCharacter::ExecutePrimaryAbility);
	PlayerInputComponent->BindAction("SecondaryAbility", IE_Pressed, this, &AGameCharacter::ExecuteSecondaryAbility);
	PlayerInputComponent->BindAction("UltimateAbility", IE_Pressed, this, &AGameCharacter::ExecuteUltimateAbility);
}

int32 AGameCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

int32 AGameCharacter::GetCurrentHealth() const
{
	return CurrentHealth;
}

float AGameCharacter::GetNormalisedHealth() const
{
	return MaxHealth / (float)CurrentHealth;
}

ETeam AGameCharacter::GetTeam() const
{
	AGameController* Controller = Cast<AGameController>(GetController());
	if (Controller == nullptr) return ETeam::Neutral;
	return Controller->GetTeam();
}

void AGameCharacter::SetTeam(ETeam Team)
{
	AGameController* Controller = Cast<AGameController>(GetController());
	if (Controller == nullptr) return;
	Controller->SetTeam(Team);
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

void AGameCharacter::ExecutePrimaryAbility()
{
	if (PrimaryAbility == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a primary ability!"), *GetName());
		return;
	}
	PrimaryAbility.GetDefaultObject()->InternalExecute(this);
}

void AGameCharacter::ExecuteSecondaryAbility()
{
	if (SecondaryAbility == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a secondary ability!"), *GetName());
		return;
	}
	SecondaryAbility.GetDefaultObject()->InternalExecute(this);
}

void AGameCharacter::ExecuteUltimateAbility()
{
	if (UltimateAbility == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have an ultimate ability!"), *GetName());
		return;
	}
	UltimateAbility.GetDefaultObject()->InternalExecute(this);
}

