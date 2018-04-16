// Fill out your copyright notice in the Description page of Project Settings.

#include "FireAssaultRifle.h"
#include "ArenaCharacter.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

#define Out

void AFireAssaultRifle::ExecuteAbility_Implementation(AActor* executor)
{
	UE_LOG(LogTemp, Warning, TEXT("executor name : %s"), *executor->GetName());

	auto* Character = Cast<AArenaCharacter>(executor);

	auto* AsssaultRiffle = Character->GetWeapon();
	if (AsssaultRiffle)
	{
		UE_LOG(LogTemp, Warning, TEXT("executor name : %s"), AsssaultRiffle);
		
	}*/

	FVector EyeLocation;
	FRotator EyeRotation;

	//funcion out que nos devolvera el punto de vista del propietario del arma
	executor->GetActorEyesViewPoint(Out EyeLocation, Out EyeRotation);

	FVector ShotDirection = EyeRotation.Vector();
	FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

	//Ajustando la collision para que no choque contra el mismo ni el propietario
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(executor);
	QueryParams.AddIgnoredActor(this);
	QueryParams.bTraceComplex = true;

	//Struct que contiene todos los datos del impacto
	FHitResult Hit;

	//Partile "Target" parameter
	FVector TracerEndPoint = TraceEnd;

	//El siguiente metodo traza una linea desde el punto de vista del propietario del arma hasta 10 metros en esa direccion.
	//Se le pasa el struct hit que sera llenado en caso de encontrar un actor con los parametros de condicion especificados
	//en el query params y retornara true si ha encontrado dicho actor.
	if (GetWorld()->LineTraceSingleByChannel(Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
	{
		//Blocking hit! Process Damage

		AActor* HitActor = Hit.GetActor();

		UGameplayStatics::ApplyPointDamage(HitActor, 20.0f, ShotDirection, Hit, executor->GetInstigatorController(), this, DamageType);

		TracerEndPoint = Hit.ImpactPoint;
	}
	DrawDebugLine(GetWorld(), EyeLocation, TraceEnd, FColor::White, false, 1.0f, 0, 1.0f);

}
