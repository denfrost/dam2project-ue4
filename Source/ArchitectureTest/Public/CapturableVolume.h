// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUtils.h"
#include "Engine/TriggerBox.h"
#include "CapturableVolume.generated.h"

/**
 *
 */
UCLASS( Blueprintable )
class ARCHITECTURETEST_API ACapturableVolume : public ATriggerBox
{
	GENERATED_BODY()
	
private:
	// The number of points needed to capture this zone (+threshold = +hard)
	UPROPERTY( EditAnywhere, Category = "Setup" )
	int32 CaptureThreshold;

	// An array of referenced actors who will be affected somehow when this zone is captured
	UPROPERTY( EditAnywhere, Category = "Setup" )
	TArray<AActor*> OnCaptureAffectedActors;

	TArray<AActor*> OverlappingActors;

	int32 CaptureState = 0;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Behaviour to be executed when this zone is captured
	UFUNCTION( BlueprintImplementableEvent )
	void OnCapture(ETeam CapturedBy);
};
