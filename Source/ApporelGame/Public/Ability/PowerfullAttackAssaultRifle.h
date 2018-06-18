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

private:

	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
	int32 ShotImpulse = 10000;
	
	
protected:

	virtual bool ExecuteAbility_Implementation(ACharacter* executor);
	
	UPROPERTY( EditDefaultsOnly, Category = "Setup" )
	TSubclassOf<AActor> ProjectileClass;
};
