// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "FireAssaultRifle.generated.h"


class AAssaultRifle;

/**
 * 
 */
UCLASS()
class APPORELGAME_API AFireAssaultRifle : public AAbility
{
	GENERATED_BODY()

protected:
	virtual void ExecuteAbility_Implementation(ACharacter* executor) override;

	void FireEffects(AAssaultRifle* AssaultRiffle, UWorld* WorldContext, FVector TraceEnd);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	TSubclassOf<UDamageType> DamageType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* TracerEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* DefaultImpactEffect;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Weapon")
	UParticleSystem* FleshImpactEffect;
};
