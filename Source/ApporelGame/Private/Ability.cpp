// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability.h"
#include "Engine/World.h"
#include "Misc/DateTime.h"
#include "GameFramework/Character.h"

void AAbility::BeginPlay()
{
	bCouldBlueprintExecute = true;
}

void AAbility::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	LastUse = 0.f;
}

int32 AAbility::GetDamage() const
{
	return Damage;
}

void AAbility::SetDamage(int32 NewDamage)
{
	this->Damage = NewDamage;
}

float AAbility::GetCooldown() const
{
	return Cooldown;
}

float AAbility::GetNormalisedRemainingCooldown() const
{
	// TODO implement
	return 0.0;
}

void AAbility::SetCooldown(float NewCooldown)
{
	this->Cooldown = NewCooldown;
}

float AAbility::GetLastUse() const
{
	return LastUse;
}

void AAbility::SetLastUse(float NewLastUse)
{
	LastUse = NewLastUse;
}

void AAbility::NotifyBlueprintCouldNotExecute()
{
	bCouldBlueprintExecute = false;
}

bool AAbility::ExecuteAbility_Implementation(ACharacter* executor)
{
	//To override in c++ child class
	return false;
}

bool AAbility::InternalExecute(ACharacter* executor)
{
	if (CanBeExecuted(executor))
	{		
		ExecuteAbility(executor);
		if (bCouldBlueprintExecute)
		{
			LastUse = executor->GetWorld()->TimeSeconds;
			return true;
		}
		bCouldBlueprintExecute = true;
	}
	return false;
}

bool AAbility::CanBeExecuted(const ACharacter* executor) const
{
	float Now = executor->GetWorld()->TimeSeconds;
	return (Now - LastUse) > Cooldown;
}
