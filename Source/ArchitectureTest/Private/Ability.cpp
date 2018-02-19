// Fill out your copyright notice in the Description page of Project Settings.

#include "Ability.h"

bool AAbility::InternalExecute()
{
	int32 Now = FDateTime::UtcNow().GetMillisecond();
	if (Now - LastUse > Cooldown)
	{
		ExecuteAbility();
		LastUse = Now;
		return true;
	}
	return false;
}

bool AAbility::CanBeExecuted()
{
	int32 Now = FDateTime::UtcNow().GetMillisecond();
	if (Now - LastUse > Cooldown)
	{
		return true;
	}
	return false;
}
