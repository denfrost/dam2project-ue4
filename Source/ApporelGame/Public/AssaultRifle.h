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

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Primary Attack | Particles")
	UParticleSystem* MuzzleEffectPrimaryAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Secondary Attack | Particles")
	UParticleSystem* MuzzleEffectSecondaryAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack | Sound")
	USoundBase* SoundPrimaryAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Secondary Attack | Sound")
	USoundBase* SoundSecondaryAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Weapon")
	TSubclassOf<UCameraShake> FireCamShake;

	virtual void ExecutePrimaryAttack() override;

	virtual void ExecuteSecondaryAttack() override;

	void PlayAttackEffects(UParticleSystem* MuzzleEffect, USoundBase* PrimaryAttackSound);

public:
	AAssaultRifle();

	FName GetMuzzleSocketName();

	FName GetTracerTargetName();

	UParticleSystem* GetMuzzleEffect();
};
