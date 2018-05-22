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

void AAssaultRifle::ExecutePrimaryAttack()
{
	Super::ExecutePrimaryAttack();

	if (MuzzleEffect)
	{
		
		UWorld* World = GetWorld();
		if (!World)
		{
			UE_LOG(LogTemp, Warning, TEXT("AAAAAAAAAAAAAA"));

		}
		//Mostramos efecto en cañon del arma
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
	}
}


