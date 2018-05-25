// Fill out your copyright notice in the Description page of Project Settings.

#include "AssaultRifle.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ArenaCharacter.h"
#include "Engine/World.h"
//TODO remove this Above Shit 

AAssaultRifle::AAssaultRifle()
{
	MuzzleSocketName = "MuzzleSocket";
	TracerTargetName = "Target";
}
void AAssaultRifle::BeginPlay()
{
	Super::BeginPlay();
}

UParticleSystem* AAssaultRifle::GetMuzzleEffect()
{
	return MuzzleEffect;
}

FName AAssaultRifle::GetMuzzleSocketName()
{
	return MuzzleSocketName;
}

FName AAssaultRifle::GetTracerTargetName()
{
	return TracerTargetName;
}

void AAssaultRifle::ExecutePrimaryAttack()
{
	Super::ExecutePrimaryAttack();

	if (MuzzleEffect)
	{
		//Mostramos efecto en ca�on del arma
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
	}

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
	}
}


