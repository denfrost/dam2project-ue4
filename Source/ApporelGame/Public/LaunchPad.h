// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "LaunchPad.generated.h"

class UParticleSystem;
class UBoxComponent;
class UStaticMeshComponent;

UCLASS()
class APPORELGAME_API ALaunchPad : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaunchPad();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UStaticMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, Category = "Setup")
	UBoxComponent* OverlapComp;

	UPROPERTY(EditAnywhere, Category = "Gameplay")
	USoundBase* LaunchSound;

	UPROPERTY(EditAnywhere, Category = "LaunchPad")
	UParticleSystem* ActivateLaunchPadEffect;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchStrength;

	UPROPERTY(EditInstanceOnly, Category = "LaunchPad")
	float LaunchPitchAngle;

	UFUNCTION()
	void OverlapLaunchPad(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
