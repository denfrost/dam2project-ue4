// Fill out your copyright notice in the Description page of Project Settings.

#include "GameCharacter.h"
#include "GamePlayerController.h"
#include "Util/Sounds.h"
#include "Runtime/Engine/Classes/GameFramework/PlayerController.h"
#include "Ability.h"

AGameCharacter::AGameCharacter()
{
	PrimaryActorTick.bCanEverTick = false;

	Team = ETeam::Neutral;
}

// Called when the game starts or when spawned
void AGameCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (PrimaryAbilityClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a primary ability!"), *GetName());
	}

	if (SecondaryAbilityClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a secondary ability!"), *GetName());
	}

	if (UltimateAbilityClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have an ultimate ability!"), *GetName());
	}

	PrimaryAbility = GetWorld()->SpawnActor<AAbility>(PrimaryAbilityClass->GetDefaultObject()->GetClass());
	PrimaryAbility->SetOwner(this);

	SecondaryAbility = GetWorld()->SpawnActor<AAbility>(SecondaryAbilityClass.GetDefaultObject()->GetClass());
	SecondaryAbility->SetOwner(this);

	UltimateAbility = GetWorld()->SpawnActor<AAbility>(UltimateAbilityClass.GetDefaultObject()->GetClass());
	UltimateAbility->SetOwner(this);

	// Set Abilities last use to -Cooldown to be able to cast them instantly at the beginning of the match
	PrimaryAbility->SetLastUse(-PrimaryAbilityClass.GetDefaultObject()->GetCooldown());
	SecondaryAbility->SetLastUse(-SecondaryAbilityClass.GetDefaultObject()->GetCooldown());
	UltimateAbility->SetLastUse(-UltimateAbilityClass.GetDefaultObject()->GetCooldown());

	// Set the current health equal to max health at the beginning
	CurrentHealth = MaxHealth;
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
	AGamePlayerController* GameController = Cast<AGamePlayerController>(GetController());
	GameController->StartSpectatingOnly();
}

float AGameCharacter::TakeDamage(
	float DamageAmount, 
	struct FDamageEvent const & DamageEvent, 
	class AController * EventInstigator, 
	AActor * DamageCauser)
{
	if(bIsDead) return 0.f;

	USounds::PlayRandomSoundAtLocation(GetWorld(), DamagedSounds, GetActorLocation());

	int32 DamagePoints = FPlatformMath::RoundToInt(DamageAmount);
	int32 DamageToApply = FMath::Clamp(DamagePoints, 0, CurrentHealth);

	CurrentHealth -= DamageToApply;
	if (CurrentHealth <= 0)
	{
		Die();
	}
	UE_LOG(LogTemp, Warning, TEXT("Damage Taken: %f\nCurrent HP: %d"), DamageAmount, CurrentHealth);
	return DamageToApply;
}

void AGameCharacter::Heal(int32 Health)
{
	CurrentHealth += Health;
	CurrentHealth = FMath::Clamp(CurrentHealth, 0, MaxHealth);
}

void AGameCharacter::Die()
{
	if (bIsDead)
	{
		return;
	}

	USounds::PlayRandomSoundAtLocation(GetWorld(), DeathSounds, GetActorLocation());

	this->SetDead(true);
	OnDeathDelegate.Broadcast(this);
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

bool AGameCharacter::IsDead() const
{
	return bIsDead;
}

void AGameCharacter::SetDead(bool IsDead)
{
	bIsDead = IsDead;
}

float AGameCharacter::GetNormalisedHealth() const
{
	return CurrentHealth / (float)MaxHealth;
}

ETeam AGameCharacter::GetTeam() const
{
	return Team;
}

void AGameCharacter::SetTeam(ETeam NewTeam)
{
	Team = NewTeam;
}

void AGameCharacter::RespawnAt(FVector Location)
{
	this->SetActorLocation(Location);
	this->SetCurrentHealth(MaxHealth);
	this->SetDead(false);
	OnRespawnDelegate.Broadcast(this);
}

void AGameCharacter::ExecutePrimaryAbility()
{
	if (PrimaryAbilityClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a primary ability!"), *GetName());
		return;
	}
	PrimaryAbility->InternalExecute(this);
}


void AGameCharacter::ExecuteSecondaryAbility()
{
	if (SecondaryAbilityClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a secondary ability!"), *GetName());
		return;
	}
	SecondaryAbility->InternalExecute(this);
}

void AGameCharacter::ExecuteUltimateAbility()
{
	if (UltimateAbilityClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have an ultimate ability!"), *GetName());
		return; 
	}
	UltimateAbility->InternalExecute(this);
}

AAbility* AGameCharacter::GetPrimaryAbility()
{
	return PrimaryAbility;
}

AAbility* AGameCharacter::GetSecondaryAbility()
{
	return SecondaryAbility;
}

AAbility* AGameCharacter::GetUltimateAbility()
{
	return UltimateAbility;
}

