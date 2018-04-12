// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameUtils/TeamUtils.h"
#include "Engine/TriggerBox.h"
#include "RespawnVolume.generated.h"

/**
 * 
 */
UCLASS()
class APPORELGAME_API ARespawnVolume : public ATriggerBox
{
	GENERATED_BODY()

private:

	// This respawn volume will spawn players of this team when they die
	UPROPERTY(EditAnywhere)
	ETeam Team;

	// The time it will take for this respawn to regenerate the dead player
	UPROPERTY(EditDefaultsOnly)
	float TimeToRespawn;

	void Respawn(class AGameCharacter* GameCharacter);

protected:

	// Called when spawned
	virtual void BeginPlay() override;

public:

	// Sets default values for this actor's properties
	ARespawnVolume();

};
