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

	PlayPrimaryAttackEffects();
}

void AAssaultRifle::ExecuteSecondaryAttack()
{
	Super::ExecuteSecondaryAttack();

	PlaySecondaryAttackEffects();
}

void AAssaultRifle::PlaySecondaryAttackEffects()
{

}

void AAssaultRifle::PlayPrimaryAttackEffects()
{
	if (MuzzleEffectPrimaryAttack)
	{
		//Mostramos efecto en cañon del arma
		UGameplayStatics::SpawnEmitterAttached(MuzzleEffectPrimaryAttack, MeshComp, MuzzleSocketName);
	}

	if (FireSound)
	{
		UGameplayStatics::PlaySoundAtLocation(GetWorld(), FireSound, GetActorLocation());
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


