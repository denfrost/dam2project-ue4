// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability.h"
#include "Engine/World.h"
#include "Misc/DateTime.h"

void AAbility::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	UE_LOG(LogTemp, Warning, TEXT("ENDPLAY"));
	LastUse = 0.f;
}

int32 AAbility::GetDamage()
{
	return Damage;
}

void AAbility::SetDamage(int32 NewDamage)
{
	this->Damage = NewDamage;
}

float AAbility::GetCooldown()
{
	return Cooldown;
}

void AAbility::SetCooldown(float NewCooldown)
{
	this->Cooldown = NewCooldown;
}

float AAbility::GetLastUse()
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
	UE_LOG(LogTemp, Warning, TEXT("Time seconds: %f"), Now);
	UE_LOG(LogTemp, Warning, TEXT("Last use: %f"), LastUse);
	if (Now - LastUse > Cooldown)
	{
		return true;
	}
	return false;
}
