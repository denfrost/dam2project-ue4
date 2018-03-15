// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability.h"
#include "Engine/World.h"
#include "Misc/DateTime.h"

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

void AAbility::InternalExecute(AActor* executor)
{
	if (CanBeExecuted(executor))
	{
		ExecuteAbility(executor);
		LastUse = executor->GetWorld()->TimeSeconds;
	}
}

bool AAbility::CanBeExecuted(const AActor* executor)
{
	float Now = executor->GetWorld()->TimeSeconds;
	if (Now - LastUse > Cooldown)
	{
		return true;
	}
	return false;
}
