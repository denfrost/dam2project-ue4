// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Util/TeamUtils.h"
#include "GameFramework/Actor.h"
#include "Runtime/Engine/Classes/Engine/EngineTypes.h"
#include "CapturableVolume.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnCaptureDelegate, ACapturableVolume*, CapturableVolume);

/**
 * A placeable volume that can be captured by members of each Team. 
 * It will trigger an OnCapture event to its derived BP in the following cases:
 * - When CaptureState == CaptureThreshold: CapturedBy: Red Team
 * - When CaptureState == -CaptureThreshold: CapturedBy: Blue Team
 * - When CaptureState changes sign after having been captured: Neutral
 */
UCLASS( Blueprintable )
class APPORELGAME_API ACapturableVolume : public AActor
{
	GENERATED_BODY()
	
private:

	// The name of this CapturableVolume, as it will be displayed on its capture
	UPROPERTY( EditAnywhere, Category = "Capturable Volume Setup" )
	FString Name;

	// The number of points needed to capture this zone (+threshold -> +hard)
	UPROPERTY( EditAnywhere, Category = "Capturable Volume Setup" )
	int32 CaptureThreshold = 50;

	// A blueprint assignable delegate which can handle the OnCapture events as the CapturableVolume overridable method itself
	UPROPERTY( BlueprintAssignable )
	FOnCaptureDelegate OnCaptureDelegate;

	// An array of referenced actors who will be affected as defined in OnCapture event when the zone is captured
	UPROPERTY( EditAnywhere, Category = "Capturable Volume Setup" )
	TArray<AActor*> OnCaptureAffectedActors;

	// The score this volume will give to the capturing team players each second
	UPROPERTY( EditAnywhere, Category = "Capturable Volume Setup" )
	int32 ScorePerSecond = 10;

	// The sound that will be played when red team captures this volume
	UPROPERTY( EditAnywhere, Category = "Capturable Volume Setup" )
	USoundBase* RedCaptureSound;

	// The sound that will be played when blue team captures this volume
	UPROPERTY( EditAnywhere, Category = "Capturable Volume Setup" )
	USoundBase* BlueCaptureSound;

	// The sound that will be played when this volume is neutralized
	UPROPERTY( EditAnywhere, Category = "Capturable Volume Setup" )
	USoundBase* NeutralizedSound;

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
	FString GetName() const;

	UFUNCTION( BlueprintCallable )
	ETeam GetOwnerTeam() const;

	UFUNCTION( BlueprintCallable )
	int32 GetCaptureState() const;

	UFUNCTION( BlueprintCallable )
	ETeam GetLastCapturingTeam() const;

	UFUNCTION( BlueprintCallable )
	float GetNormalizedCaptureState() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Behavior to be executed when this zone is captured
	UFUNCTION( BlueprintImplementableEvent )
	void OnCapture(ETeam CapturedBy, const TArray<AActor*>& AffectedActors);
};
