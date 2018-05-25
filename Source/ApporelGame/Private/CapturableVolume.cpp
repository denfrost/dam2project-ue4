// Fill out your copyright notice in the Description page of Project Settings.

#include "CapturableVolume.h"
#include "ArenaCharacter.h"
#include "GameUtils/TeamUtils.h"

#define OUT

// Sets default values
ACapturableVolume::ACapturableVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

int32 ACapturableVolume::GetCaptureState() const
{
	return CaptureState;
}

void ACapturableVolume::BeginPlay()
{
	Super::BeginPlay();

	LastCapturingTeam = ETeam::Neutral;
}

// Called every frame, so please REFACTOR THIS
void ACapturableVolume::Tick(float DeltaTime)
{
	GetOverlappingActors(OUT OverlappingActors, AArenaCharacter::StaticClass());
	if (OverlappingActors.Num() == 0) return;

	// Red team has capture advantage
	if (CaptureState >= 0)
	{
		// If the point is 100% captured, set red team as last capturing team and notify BP
		if (CaptureState >= CaptureThreshold && LastCapturingTeam != ETeam::Red)
		{
			LastCapturingTeam = ETeam::Red;
			OnCapture(ETeam::Red, OnCaptureAffectedActors);
		}

		// If the last capturing team isn't red but it has the advantage, then red team has neutralized the zone
		else if (LastCapturingTeam != ETeam::Red && LastCapturingTeam != ETeam::Neutral)
		{
			LastCapturingTeam = ETeam::Neutral;
			OnCapture(ETeam::Neutral, OnCaptureAffectedActors);
		}
	}

	// Same logic with blue team
	if (CaptureState <= 0)
	{
		if (CaptureState <= -CaptureThreshold && LastCapturingTeam != ETeam::Blue)
		{
			LastCapturingTeam = ETeam::Blue;
			OnCapture(ETeam::Blue, OnCaptureAffectedActors);
		}

		else if (LastCapturingTeam != ETeam::Blue && LastCapturingTeam != ETeam::Neutral)
		{
			LastCapturingTeam = ETeam::Neutral;
			OnCapture(ETeam::Neutral, OnCaptureAffectedActors);
		}
	}

	int32 TeamFactor = 0;
	for (AActor* Actor : OverlappingActors)
	{
		AArenaCharacter* ArenaCharacter = Cast<AArenaCharacter>(Actor);
		TeamFactor += ( ArenaCharacter->GetTeam() == ETeam::Red ) ? 1 : -1;
	}

	CaptureState += TeamFactor;
	CaptureState = FMath::Clamp(CaptureState, -CaptureThreshold, CaptureThreshold);
}
