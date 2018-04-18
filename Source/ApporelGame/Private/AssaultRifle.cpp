// Fill out your copyright notice in the Description page of Project Settings.

#include "AssaultRifle.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"

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
		UE_LOG(LogTemp, Warning, TEXT("%s"), *MeshComp->GetFName().ToString());
		//Mostramos efecto en cañon del arma
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
	}
}


