// Fill out your copyright notice in the Description page of Project Settings.

#include "BlackHole.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "ArenaCharacter.h"
#include "TeamUtils.h"
#include "Components/CapsuleComponent.h"

// Sets default values
ABlackHole::ABlackHole()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	RootComponent = MeshComp;

	SphereSuckerRadius = 60.f;

	SphereCompSuck = CreateDefaultSubobject<USphereComponent>(TEXT("SphereSuck"));
	SphereCompSuck->SetSphereRadius(SphereSuckerRadius);
	SphereCompSuck->SetupAttachment(MeshComp);

	InitialLifeSpan = 5.f;
	SuckerForce = 5;
}

// Called when the game starts or when spawned
void ABlackHole::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ABlackHole::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	TArray<AActor*> OverlappingActors;
	SphereCompSuck->GetOverlappingActors(OUT OverlappingActors, AArenaCharacter::StaticClass());

	for (int32 i = 0; i < OverlappingActors.Num(); i++)
	{
		AArenaCharacter* Actor = Cast<AArenaCharacter>(OverlappingActors[i]);
		if (!Actor)
		{
			UE_LOG(LogTemp, Warning, TEXT("No actor"));
		}

		AArenaCharacter* Owner = Cast<AArenaCharacter>(GetOwner());
		if (!Owner)
		{
			UE_LOG(LogTemp, Warning, TEXT("No Owner"));
		}

		if( Owner->GetTeam() != Actor->GetTeam() )
		{
			const float SphereRadius = SphereCompSuck->GetScaledSphereRadius();
			UE_LOG(LogTemp, Warning, TEXT("Sucking %s"), *Actor->GetName());

			FVector DistanceActorToBlackHole = GetActorLocation() - Actor->GetActorLocation();
			DistanceActorToBlackHole.Normalize();
			Actor->AddActorWorldOffset(DistanceActorToBlackHole * SuckerForce);
		}
	}
}

