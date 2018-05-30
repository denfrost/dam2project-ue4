// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Util/TeamUtils.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

class AAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeathDelegate, AGameCharacter*, GameCharacter);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnRespawnDelegate, AGameCharacter*, GameCharacter);

UCLASS( abstract )
class APPORELGAME_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

protected:

	// Called when spawned
	virtual void BeginPlay() override;

	// The initial health of the character (could be modified in game)
	UPROPERTY( EditDefaultsOnly, Category = "Game Character Setup | Stats" )
	int32 MaxHealth;

	int32 CurrentHealth;

	UPROPERTY( EditDefaultsOnly, Category = "Game Character Setup | Stats" )
	int32 Armor;

	bool bIsDead;

	UPROPERTY( EditAnywhere )
	ETeam Team;

	UPROPERTY(EditAnywhere, Category = "Game Character Setup | Sound")
	TArray<USoundBase*> DeathSounds;

	UPROPERTY(EditAnywhere, Category = "Game Character Setup | Sound")
	TArray<USoundBase*> DamagedSounds;

	UPROPERTY( EditDefaultsOnly, Category = "Game Character Setup | Abilities" )
	TSubclassOf<AAbility> PrimaryAbilityClass = nullptr;

	AAbility* PrimaryAbility;

	UPROPERTY( EditDefaultsOnly, Category = "Game Character Setup | Abilities" )
	TSubclassOf<AAbility> SecondaryAbilityClass = nullptr;

	AAbility* SecondaryAbility;

	UPROPERTY( EditDefaultsOnly, Category = "Game Character Setup | Abilities" )
	TSubclassOf<AAbility> UltimateAbilityClass = nullptr;

	AAbility* UltimateAbility;

public:	
	
	AGameCharacter();

	// The receiver of this character's death event
	UPROPERTY( BlueprintAssignable )
	FOnDeathDelegate OnDeathDelegate;

	// The receiver of this character's respawn event
	UPROPERTY( BlueprintAssignable )
	FOnRespawnDelegate OnRespawnDelegate;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	// Delegate method for PlayerController#StartSpectatingOnly
	virtual void StartSpectatingOnly();

	// Called by the engine when actor damage is dealt
	virtual float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent, class AController * EventInstigator, AActor * DamageCauser) override;

	// Restores the specified amount of Health to the Character, stopping at MaxHealth
	UFUNCTION( BlueprintCallable )
	void Heal(int32 Health);

	// Generic death procedure
	UFUNCTION( BlueprintCallable )
	virtual void Die();

	UFUNCTION( BlueprintCallable )
	int32 GetMaxHealth() const;

	UFUNCTION( BlueprintCallable )
	int32 GetCurrentHealth() const;

	UFUNCTION( BlueprintCallable )
	void SetCurrentHealth(int32 Health);

	UFUNCTION( BlueprintCallable )
	bool IsDead() const;

	UFUNCTION( BlueprintCallable )
	void SetDead(bool IsDead);

	// Returns the current health as a value between 0.0 and 1.0
	UFUNCTION( BlueprintCallable )
	float GetNormalisedHealth() const;

	UFUNCTION( BlueprintCallable )
	ETeam GetTeam() const;

	UFUNCTION( BlueprintCallable )
	void SetTeam(ETeam NewTeam);

	virtual void RespawnAt(FVector Location);

	virtual void ExecutePrimaryAbility();

	virtual void ExecuteSecondaryAbility();

	virtual void ExecuteUltimateAbility();

	virtual AAbility* GetPrimaryAbility();

	virtual AAbility* GetSecondaryAbility();

	virtual AAbility* GetUltimateAbility();
};
