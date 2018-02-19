// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "GameCharacter.generated.h"

class AGameController;

UCLASS( abstract )
class ARCHITECTURETEST_API AGameCharacter : public ACharacter
{
	GENERATED_BODY()

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
		int32 Health;

	UPROPERTY(EditAnywhere)
		int32 Armor;
	
	AGameController* Controller = nullptr;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void OnDeath();

	virtual bool Respawn();

	virtual bool PrimaryAbility();

	virtual bool SecondaryAbility();

	virtual bool UltimateAbility();
};
