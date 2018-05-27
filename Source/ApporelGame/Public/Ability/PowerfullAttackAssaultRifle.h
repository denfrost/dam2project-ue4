// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Ability.h"
#include "PowerfullAttackAssaultRifle.generated.h"


class AAssaultRifle;

/**
 * 
 */
UCLASS()
class APPORELGAME_API APowerfullAttackAssaultRifle : public AAbility
{
	GENERATED_BODY()
	
	
protected:
	virtual void ExecuteAbility_Implementation(ACharacter* executor);
	
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Setup")
	TSubclassOf<AActor> ProjectileClass;
};
