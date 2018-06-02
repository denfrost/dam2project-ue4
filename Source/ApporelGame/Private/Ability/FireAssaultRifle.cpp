#include "FireAssaultRifle.h"
#include "ArenaCharacter.h"
#include "AssaultRifle.h"
#include "DrawDebugHelpers.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystemComponent.h"
#include "ApporelGame.h"

//Declare debug Var
static int32 DebugWeaponDrawing = 0;
FAutoConsoleVariableRef CVARDebugWeaponDrawing(
	TEXT("APPORELBOTNA.DebugWeapons"),
	DebugWeaponDrawing,
	TEXT("Draw Debug Lines for Weapons"),
	ECVF_Cheat);

#define Out

bool AFireAssaultRifle::ExecuteAbility_Implementation(ACharacter* executor)
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

	FVector ShotDirection = EyeRotation.Vector();
	FVector TraceEnd = EyeLocation + (ShotDirection * 10000);

	//Ajustando la collision para que no choque contra el pawn ni el arma
	FCollisionQueryParams QueryParams;
	QueryParams.AddIgnoredActor(executor);
	QueryParams.AddIgnoredActor(AssaultRiffle);
	QueryParams.bTraceComplex = true;
	QueryParams.bReturnPhysicalMaterial = true;

	//Struct que contiene todos los datos del impacto
	FHitResult Hit;

	//Partile "Target" parameter
	FVector TracerEndPoint = TraceEnd;

	//El siguiente metodo traza una linea desde el punto de vista del propietario del arma hasta 100 metros en esa direccion.
	//Se le pasa el struct hit que sera llenado en caso de encontrar un actor con los parametros de condicion especificados
	//en el query params y retornara true si ha encontrado dicho actor.
	if (WorldContext->LineTraceSingleByChannel(Out Hit, EyeLocation, TraceEnd, COLLISION_WEAPON, QueryParams))
	{
		//Blocking hit! Process Damage
		AActor* HitActor = Hit.GetActor();

		EPhysicalSurface SurfaceType = UPhysicalMaterial::DetermineSurfaceType(Hit.PhysMaterial.Get());

		float ActualDamage = GetDamage();
		if (SurfaceType == SURFACE_FLESH_VULNERABLE)
		{
			ActualDamage *= 4.f;
		}

		UGameplayStatics::ApplyPointDamage(HitActor, ActualDamage, ShotDirection, Hit, executor->GetInstigatorController(), Character, DamageType);

		UParticleSystem* SelectedEffect = nullptr;
		switch (SurfaceType)
		{
		case SURFACE_FLESH_DEFAULT:
		case SURFACE_FLESH_VULNERABLE:
			SelectedEffect = FleshImpactEffect;
			break;
		default:
			SelectedEffect = DefaultImpactEffect;
			break;
		}
		
		if (SelectedEffect)
		{
			//mostramos el efecto en el lugar de impacto
			UGameplayStatics::SpawnEmitterAtLocation(WorldContext, SelectedEffect, Hit.ImpactPoint, Hit.ImpactNormal.Rotation());
		}
		TracerEndPoint = Hit.ImpactPoint;
	}

	//Debug testing
	if(DebugWeaponDrawing > 0)
	{
		DrawDebugLine( WorldContext, EyeLocation, TracerEndPoint, FColor::Yellow, false, 1.5f, 0, 1.0f);
	}

	FireEffects(AssaultRiffle, WorldContext, TracerEndPoint);

	return true;
}

void AFireAssaultRifle::FireEffects(AAssaultRifle* AssaultRiffle, UWorld* WorldContext, FVector TraceEnd)
{
	if (TracerEffect)
	{
		FVector MuzzleLocation = AssaultRiffle->GetMeshComp()->GetSocketLocation(AssaultRiffle->GetMuzzleSocketName());
		UParticleSystemComponent* TracerComp = UGameplayStatics::SpawnEmitterAtLocation(WorldContext, TracerEffect, MuzzleLocation);
		if (TracerComp)
		{
			TracerComp->SetVectorParameter(AssaultRiffle->GetTracerTargetName(), TraceEnd);
		}
	}
}
