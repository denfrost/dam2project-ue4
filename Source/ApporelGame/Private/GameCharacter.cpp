// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCharacter.h"
#include "GameController.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
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

	// Set the current health equal to max health at the beginning
	CurrentHealth = MaxHealth;
}

AGameCharacter::AGameCharacter()
{
	PrimaryActorTick.bCanEverTick = false;
}

// Called to bind functionality to input
void AGameCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("PrimaryAbility", IE_Pressed, this, &AGameCharacter::ExecutePrimaryAbility);
	PlayerInputComponent->BindAction("SecondaryAbility", IE_Pressed, this, &AGameCharacter::ExecuteSecondaryAbility);
	PlayerInputComponent->BindAction("UltimateAbility", IE_Pressed, this, &AGameCharacter::ExecuteUltimateAbility);
}

void AGameCharacter::StartSpectatingOnly()
{
	// TODO remove technical debt here when AI is implemented, otherwise it won't be able to use this class
	AGameController* GameController = Cast<AGameController>(GetController());
	GameController->StartSpectatingOnly();
}

float AGameCharacter::TakeDamage(
	float DamageAmount, 
	struct FDamageEvent const & DamageEvent, 
	class AController * EventInstigator, 
	AActor * DamageCauser)
{
	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		OnDeathDelegate.Broadcast(this);
	}
	UE_LOG(LogTemp, Warning, TEXT("Damage Taken: %f\nCurrent HP: %d"), DamageAmount, CurrentHealth);
	return DamageToApply;
}

void AGameCharacter::Heal(int32 Health)
{
	CurrentHealth += Health;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
}

int32 AGameCharacter::GetMaxHealth() const
{
	return MaxHealth;
}

int32 AGameCharacter::GetCurrentHealth() const
{
	return CurrentHealth;
}

void AGameCharacter::SetCurrentHealth(int32 Health)
{
	CurrentHealth = Health;
}

float AGameCharacter::GetNormalisedHealth() const
{
	return CurrentHealth / (float)MaxHealth;
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

void AGameCharacter::RespawnAt(FVector Location)
{
	this->SetActorLocation(Location);
	this->SetCurrentHealth(MaxHealth);
}

void AGameCharacter::ExecutePrimaryAbility()
{
	if (PrimaryAbility == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a primary ability!"), *GetName());
		return;
	}
	
	//spawn
	AAbility* Ability = GetWorld()->SpawnActor<AAbility>(PrimaryAbility.GetDefaultObject()->GetClass());
	Ability->InternalExecute(this);
}

void AGameCharacter::ExecuteSecondaryAbility()
{
	if (SecondaryAbility == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a secondary ability!"), *GetName());
		return;
	}
	AAbility* Ability = GetWorld()->SpawnActor<AAbility>(SecondaryAbility.GetDefaultObject()->GetClass());
	Ability->InternalExecute(this);
}

void AGameCharacter::ExecuteUltimateAbility()
{
	if (UltimateAbility == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have an ultimate ability!"), *GetName());
		return;
	}
	AAbility* Ability = GetWorld()->SpawnActor<AAbility>(UltimateAbility.GetDefaultObject()->GetClass());
	Ability->InternalExecute(this);
}

