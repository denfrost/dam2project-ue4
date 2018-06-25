// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

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

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Assault Rifle Setup")
	FName MuzzleSocketName;
	
	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = "Assault Rifle Setup")
	FName TracerTargetName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Assault Rifle Setup | Primary Attack | Particles")
	UParticleSystem* MuzzleEffectPrimaryAttack;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Assault Rifle Setup | Secondary Attack | Particles")
	UParticleSystem* MuzzleEffectSecondaryAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Assault Rifle Setup")
	TSubclassOf<UCameraShake> FireCamShake;

	virtual bool ExecutePrimaryAttack() override;

	virtual bool ExecuteSecondaryAttack() override;

	void PlayAttackEffects(UParticleSystem* MuzzleEffect);

public:
	AAssaultRifle();

	FName GetMuzzleSocketName();

	FName GetTracerTargetName();

	UParticleSystem* GetMuzzleEffect();
};
