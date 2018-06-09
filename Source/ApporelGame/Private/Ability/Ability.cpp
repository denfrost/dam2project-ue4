// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability.h"
#include "Engine/World.h"
#include "Misc/DateTime.h"
#include "Util/Sounds.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "Runtime/Engine/Public/TimerManager.h"
#include "GameFramework/Character.h"

void AAbility::BeginPlay()
{
	bHasCooldownEnded = true;
	bCouldBlueprintExecute = true;
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

FTimerHandle AAbility::GetCooldownTimerHandle() const
{
	return CooldownTimerHandle;
}

float AAbility::GetRemainingCooldown() const
{
	return FMath::Clamp(
		GetWorld()->GetTimerManager().GetTimerRemaining(CooldownTimerHandle), 
		0.0f, 
		Cooldown);
}

float AAbility::GetNormalizedRemainingCooldown() const
{
	return GetRemainingCooldown() / Cooldown;
}

void AAbility::SetCooldown(float NewCooldown)
{
	this->Cooldown = NewCooldown;
}

void AAbility::StartCooldownTimer()
{
	bHasCooldownEnded = false;
	GetWorldTimerManager().SetTimer
	(
		CooldownTimerHandle,
		this,
		&AAbility::NotifyCooldownEnded,
		Cooldown,
		false
	);
}

void AAbility::NotifyCooldownEnded()
{
	bHasCooldownEnded = true;
}

void AAbility::NotifyBlueprintCouldNotExecute()
{
	bCouldBlueprintExecute = false;
}

bool AAbility::ExecuteAbility_Implementation(ACharacter* executor)
{
	// To override in c++ child class
	return false;
}

bool AAbility::InternalExecute(ACharacter* executor)
{
	if (HasCooldownEnded())
	{		
		ExecuteAbility(executor);
		if (bCouldBlueprintExecute)
		{
			USounds::PlaySoundAtLocation(executor->GetWorld(), Sound, executor->GetActorLocation());
			StartCooldownTimer();
			return true;
		}
		bCouldBlueprintExecute = true;
	}
	return false;
}

bool AAbility::HasCooldownEnded() const
{
	return bHasCooldownEnded;
}
