// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "AssaultRifle.generated.h"

class UParticleSystem;

/**
 * 
 */
UCLASS()
class APPORELGAME_API AAssaultRifle : public AWeapon
{
	GENERATED_BODY()
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName MuzzleSocketName;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* MuzzleEffect;

	UParticleSystem* GetMuzzleEffect();

	FName GetMuzzleSocketName();

	virtual void ExecutePrimaryAttack() override;

public:
	AAssaultRifle();
};
