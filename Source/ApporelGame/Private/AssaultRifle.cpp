// Fill out your copyright notice in the Description page of Project Settings.

#include "AssaultRifle.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "Components/SkeletalMeshComponent.h"
#include "Particles/ParticleSystemComponent.h"
#include "ArenaCharacter.h"
#include "Engine/World.h"

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
	return MuzzleEffectPrimaryAttack;
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

	PlayAttackEffects(MuzzleEffectPrimaryAttack, SoundPrimaryAttack);
}

void AAssaultRifle::ExecuteSecondaryAttack()
{
	Super::ExecuteSecondaryAttack();

	PlayAttackEffects(MuzzleEffectSecondaryAttack, SoundSecondaryAttack);
}

void AAssaultRifle::PlayAttackEffects(UParticleSystem* MuzzleEffect, USoundBase* AttackSound)
{
	if (MuzzleEffect)
	{
		//Mostramos efecto en cañon del arma
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffect, MeshComp, MuzzleSocketName);
	}

	if (AttackSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), AttackSound, GetActorLocation());
	}

	//Shake camera
	APawn* MyOwner = Cast<APawn>(GetOwner());
	if (MyOwner)
	{
		APlayerController* PC = Cast<APlayerController>(MyOwner->GetController());
		if (PC)
		{
			PC->ClientPlayCameraShake(FireCamShake);
		}
	}
}


