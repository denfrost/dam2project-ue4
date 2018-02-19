// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

class AGameController;
class AAbility;

UCLASS( abstract )
class ARCHITECTURETEST_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY( EditDefaultsOnly, Category = "Character Setup" )
	int32 Health;

	UPROPERTY( EditDefaultsOnly, Category = "Character Setup")
	int32 Armor;

	UPROPERTY( EditDefaultsOnly, Category = "Character Setup")
	TSubclassOf<AAbility> PrimaryAbility;

	UPROPERTY( EditDefaultsOnly, Category = "Character Setup")
	TSubclassOf<AAbility> SecondaryAbility;

	UPROPERTY( EditDefaultsOnly, Category = "Character Setup")
	TSubclassOf<AAbility> UltimateAbility;
	
	AGameController* Controller = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnDeath();

	virtual bool Respawn();

	virtual bool ExecutePrimaryAbility();

	virtual bool ExecuteSecondaryAbility();

	virtual bool ExecuteUltimateAbility();
};
