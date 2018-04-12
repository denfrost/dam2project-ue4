// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUtils/TeamUtils.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

class AGameController;
class AAbility;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, AGameCharacter*, GameCharacter);

UCLASS( abstract )
class APPORELGAME_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when spawned
	virtual void BeginPlay() override;

	FOnDeath OnDeathEvent;

	// The initial health of the character (could be modified in game)
	UPROPERTY( EditDefaultsOnly, Category = "Character Setup" )
	int32 MaxHealth;

	int32 CurrentHealth;

	UPROPERTY( EditDefaultsOnly, Category = "Character Setup" )
	int32 Armor;

	UPROPERTY( EditDefaultsOnly, Category = "Character Setup" )
	TSubclassOf<AAbility> PrimaryAbility = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Character Setup" )
	TSubclassOf<AAbility> SecondaryAbility = nullptr;

	UPROPERTY( EditDefaultsOnly, Category = "Character Setup" )
	TSubclassOf<AAbility> UltimateAbility = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION( BlueprintCallable )
	int32 GetMaxHealth() const;

	UFUNCTION( BlueprintCallable )
	int32 GetCurrentHealth() const;

	// Returns the current health as a value between 0 and 1
	UFUNCTION( BlueprintCallable )
	float GetNormalisedHealth() const;

	UFUNCTION( BlueprintCallable )
	ETeam GetTeam() const;

	UFUNCTION( BlueprintCallable )
	void SetTeam(ETeam Team);

	void OnDeath();

	virtual bool Respawn();

	virtual void ExecutePrimaryAbility();

	virtual void ExecuteSecondaryAbility();

	virtual void ExecuteUltimateAbility();
};
