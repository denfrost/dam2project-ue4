#include "FireAssaultRifle.h"
#include "ArenaCharacter.h"
#include "AssaultRifle.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"

#define Out

void AFireAssaultRifle::ExecuteAbility_Implementation(ACharacter* executor)
{	
	UWorld* WorldContext = executor->GetWorld();
	if (!WorldContext)
	{
		UE_LOG(LogTemp, Warning, TEXT("NO World Context Available!"));
		return;
	}

	auto* Character = Cast<AArenaCharacter>(executor);
	if (!Character)
	{
		UE_LOG(LogTemp, Warning, TEXT("No Pawn"));
		return;
	}

	AAssaultRifle* AsssaultRiffle = Cast<AAssaultRifle>(Character->GetCurrentWeapon());
	if (!AsssaultRiffle)
	{
		UE_LOG(LogTemp, Warning, TEXT("No weapon"));
		return;
	}

	FVector EyeLocation;
	FRotator EyeRotation;

	//funcion out que nos devolvera el punto de vista del propietario del arma
	executor->GetActorEyesViewPoint(Out EyeLocation, Out EyeRotation);

	FVector ShotDirection = EyeRotation.Vector();
	FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

	//Ajustando la collision para que no choque contra el pawn ni el arma
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(executor);
	QueryParams.AddIgnoredActor(AsssaultRiffle);
	QueryParams.bTraceComplex = true;

	//Struct que contiene todos los datos del impacto
	FHitResult Hit;

	//Partile "Target" parameter
	FVector TracerEndPoint = TraceEnd;

	//El siguiente metodo traza una linea desde el punto de vista del propietario del arma hasta 100 metros en esa direccion.
	//Se le pasa el struct hit que sera llenado en caso de encontrar un actor con los parametros de condicion especificados
	//en el query params y retornara true si ha encontrado dicho actor.
	if (WorldContext->LineTraceSingleByChannel(Out Hit, EyeLocation, TraceEnd, ECC_Visibility, QueryParams))
	{
		//Blocking hit! Process Damage

		AActor* HitActor = Hit.GetActor();
		UE_LOG(LogTemp, Warning, TEXT("HitActor name : %s"), *HitActor->GetName());

		UGameplayStatics::ApplyPointDamage(HitActor, 20.0f, ShotDirection, Hit, executor->GetInstigatorController(), this, DamageType);

		TracerEndPoint = Hit.ImpactPoint;
	}
	DrawDebugLine( WorldContext, EyeLocation, TraceEnd, FColor::Yellow, false, 3.0f, 0, 3.0f);


// 	if (TracerEffect)
// 	{
// 		FVector MuzzleLocation = MeshComp->GetSocketLocation(AsssaultRiffle->GetMuzzleSocketName());
// 		UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(WorldContext, TracerEffect, MuzzleLocation);
// 		if (TracerComp)
// 		{
// 			TracerComp->SetVectorParameter(TracerTargetName, TracerEndPoint);
// 		}
// 	}
}
