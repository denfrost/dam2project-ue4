// Fill out your copyright notice in the Description page of Project Settings.

#include "CapturableVolume.h"
#include "ArenaCharacter.h"
#include "GameController.h"
#include "GameUtils.h"

#define OUT

// Called every frame
void ACapturableVolume::Tick(float DeltaTime)
{
	GetOverlappingActors(OUT OverlappingActors, AArenaCharacter::StaticClass());
	if (OverlappingActors.Num() == 0) return;

	int32 TeamFactor = 0;
	for (AActor* Actor : OverlappingActors)
	{
		AArenaCharacter* ArenaCharacter = Cast<AArenaCharacter>(Actor);
		AGameController* Controller = Cast<AGameController>(ArenaCharacter->GetController());
		TeamFactor = ( Controller->GetTeam() == ETeam::Red ) ? TeamFactor + 1 : TeamFactor - 1;
	}
	CaptureState += TeamFactor;
	
	// if abs(CaptureState) >= CaptureThreshold
		// OnCapture(ETeam::Red)
	// else if abs(CaptureState) <= -CaptureThreshold
		// OnCapture(ETeam::Blue)
}
