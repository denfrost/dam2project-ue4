// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Util/TeamUtils.h"
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
	UPROPERTY( EditAnywhere )
	ETeam Team;

	// The time it will take for this respawn to regenerate the dead player
	UPROPERTY( EditDefaultsOnly )
	float TimeToRespawn;

	UFUNCTION( NetMulticast, Reliable )
	void ReceiveDeadCharacter(AGameCharacter* Dead, AGameCharacter* Killer);

	UFUNCTION( NetMulticast, Reliable )
	void RespawnCharacter();

	TQueue<AGameCharacter*> CharactersToRespawn;

protected:

	// Called when spawned
	virtual void BeginPlay() override;

public:

	// Sets default values for this actor's properties
	ARespawnVolume();

};
