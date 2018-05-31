// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Util/TeamUtils.h"
#include "Engine/TriggerBox.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "CapturableVolume.generated.h"

/**
 * A placeable volume that can be captured by members of each Team. 
 * It will trigger an OnCapture event to its derived BP in the following cases:
 * - When CaptureState == CaptureThreshold: CapturedBy: Red Team
 * - When CaptureState == -CaptureThreshold: CapturedBy: Blue Team
 * - When CaptureState changes sign after having been captured: Neutral
 */
UCLASS( Blueprintable )
class APPORELGAME_API ACapturableVolume : public ATriggerBox
{
	GENERATED_BODY()
	
private:

	// The number of points needed to capture this zone (+threshold -> +hard)
	UPROPERTY( EditAnywhere, Category = "Setup" )
	int32 CaptureThreshold = 50;

	// An array of referenced actors who will be affected as defined in OnCapture event when the zone is captured
	UPROPERTY( EditAnywhere, Category = "Setup" )
	TArray<AActor*> OnCaptureAffectedActors;

	// The score this volume will give to the capturing team players each second
	UPROPERTY( EditAnywhere, Category = "Setup" )
	int32 ScorePerSecond = 10;

	TArray<AActor*> OverlappingActors;

	int32 CaptureState = 0;

	ETeam LastCapturingTeam;

	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;

	void StartScoreTimerForTeam(ETeam Team);

	UFUNCTION()
	void GiveScoreToTeam(ETeam Team);

protected:

	// Called when spawned
	virtual void BeginPlay() override;

public:
	// Sets default values for this actor's properties
	ACapturableVolume();

	UFUNCTION( BlueprintCallable )
	ETeam GetOwnerTeam();

	UFUNCTION( BlueprintCallable )
	int32 GetCaptureState() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Behavior to be executed when this zone is captured
	UFUNCTION( BlueprintImplementableEvent )
	void OnCapture(ETeam CapturedBy, const TArray<AActor*>& AffectedActors);
};
