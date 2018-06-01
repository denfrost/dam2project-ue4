// Fill out your copyright notice in the Description page of Project Settings.

#include "CapturableVolume.h"
#include "ArenaCharacter.h"
#include "Util/TeamUtils.h"
#include "Util/Sounds.h"
#include "ApporelGameGameModeBase.h"

#define OUT

// Sets default values
ACapturableVolume::ACapturableVolume()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

FString ACapturableVolume::GetName() const
{
	return Name;
}

ETeam ACapturableVolume::GetOwnerTeam() const
{
	return LastCapturingTeam;
}

int32 ACapturableVolume::GetCaptureState() const
{
	return CaptureState;
}

ETeam ACapturableVolume::GetLastCapturingTeam() const
{
	return LastCapturingTeam;
}

float ACapturableVolume::GetNormalizedCaptureState() const
{
	float NormalizedCaptureState = CaptureState / (float)CaptureThreshold;
	return FMath::Clamp(NormalizedCaptureState, -1.f, 1.f);
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
			USounds::PlaySound2D(GetWorld(), RedCaptureSound);
			OnCaptureDelegate.Broadcast(this);
			OnCapture(ETeam::Red, OnCaptureAffectedActors);
			StartScoreTimerForTeam(ETeam::Red);
		}

		// If the last capturing team isn't red but it has the advantage, then red team has neutralized the zone
		else if (LastCapturingTeam != ETeam::Red && LastCapturingTeam != ETeam::Neutral)
		{
			LastCapturingTeam = ETeam::Neutral;
			USounds::PlaySound2D(GetWorld(), NeutralizedSound);
			OnCaptureDelegate.Broadcast(this);
			OnCapture(ETeam::Neutral, OnCaptureAffectedActors);
			this->GetWorldTimerManager().ClearTimer(TimerHandle);
		}
	}

	// Same logic with blue team
	if (CaptureState <= 0)
	{
		if (CaptureState <= -CaptureThreshold && LastCapturingTeam != ETeam::Blue)
		{
			LastCapturingTeam = ETeam::Blue;
			USounds::PlaySound2D(GetWorld(), BlueCaptureSound);
			OnCaptureDelegate.Broadcast(this);
			OnCapture(ETeam::Blue, OnCaptureAffectedActors);
			StartScoreTimerForTeam(ETeam::Blue);
		}

		else if (LastCapturingTeam != ETeam::Blue && LastCapturingTeam != ETeam::Neutral)
		{
			LastCapturingTeam = ETeam::Neutral;
			USounds::PlaySound2D(GetWorld(), NeutralizedSound);
			OnCaptureDelegate.Broadcast(this);
			OnCapture(ETeam::Neutral, OnCaptureAffectedActors);
			this->GetWorldTimerManager().ClearTimer(TimerHandle);
		}
	}

	int32 TeamFactor = 0;
	for (AActor* Actor : OverlappingActors)
	{
		AArenaCharacter* ArenaCharacter = Cast<AArenaCharacter>(Actor);
		TeamFactor += ( !ArenaCharacter->IsDead() && ArenaCharacter->GetTeam() == ETeam::Red ) ? 1 : -1;
	}

	CaptureState += TeamFactor;
	CaptureState = FMath::Clamp(CaptureState, -CaptureThreshold, CaptureThreshold);
}

void ACapturableVolume::StartScoreTimerForTeam(ETeam Team)
{
	TimerDelegate.BindUFunction(this, FName("GiveScoreToTeam"), Team);
	this->GetWorldTimerManager().SetTimer(TimerHandle, TimerDelegate, 1.f, true);
}

void ACapturableVolume::GiveScoreToTeam(ETeam Team)
{
	AApporelGameGameModeBase* GameMode = Cast<AApporelGameGameModeBase>(this->GetWorld()->GetAuthGameMode());
	GameMode->IncrementScore(Team, ScorePerSecond);
}
