// Fill out your copyright notice in the Description page of Project Settings.

#include "PowerfullAttackAssaultRifle.h"
#include "ArenaCharacter.h"
#include "ApporelGame.h"
#include "AssaultRifle.h"

#define Out

bool APowerfullAttackAssaultRifle::ExecuteAbility_Implementation(ACharacter* executor)
{
	UWorld* WorldContext = executor->GetWorld();
	if (!WorldContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("No world context available!"));
		return false;
	}

	AArenaCharacter* Character = Cast<AArenaCharacter>(executor);
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Pawn"));
		return false;
	}

	AAssaultRifle* AssaultRiffle = Cast<AAssaultRifle>(Character->GetCurrentWeapon());
	if (!AssaultRiffle)
	{
		UE_LOG(LogTemp, Warning, TEXT("No weapon"));
		return false;
	}

	FVector EyeLocation;
	FRotator EyeRotation;

	//Punto de vista del propietario del arma
	executor->GetActorEyesViewPoint(Out EyeLocation, Out EyeRotation);

	FVector MuzzleLocation = AssaultRiffle->GetMeshComp()->GetSocketLocation(AssaultRiffle->GetMuzzleSocketName());

	FVector ShotDirection = EyeRotation.Vector();
	FVector TraceEnd = EyeLocation + (ShotDirection * 10000);
	FHitResult Hit;

	//Ajustando la collision para que no choque contra el pawn ni el arma
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(executor);
	QueryParams.AddIgnoredActor(AssaultRiffle);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;

	FRotator DesiredRotation = EyeRotation;

	//Lugar de impacto
	if(GetWorld()->LineTraceSingleByChannel(Out Hit, EyeLocation, TraceEnd, COLLISION_WEAPON, QueryParams))
	{	
		//vector de distancia entre la ubicacion del cañon del arma y el lugar de impacto
		FVector Distance = Hit.Location - MuzzleLocation;
		DesiredRotation = Distance.Rotation();
	}

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SpawnParams.Owner = executor;

	GetWorld()->SpawnActor<AActor>(ProjectileClass, MuzzleLocation, DesiredRotation, SpawnParams);
	return true;
}
