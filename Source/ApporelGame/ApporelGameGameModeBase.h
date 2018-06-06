// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "Util/TeamUtils.h"
#include "ApporelGameGameModeBase.generated.h"

USTRUCT(BlueprintType)
struct FPlayerStats
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	FName Name;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Kills;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Deaths; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Assistances;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Stats")
	int32 Score;
};


UCLASS()
class APPORELGAME_API AApporelGameGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

private:
	bool bIsGameOver;
	
protected:
	int32 ScoreTeamBlue;
	int32 ScoreTeamRed;

	UPROPERTY( EditDefaultsOnly , Category = "Win")
	int32 ScoreToWin = 5000;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category = "Player Stats" )
	TMap<AGameCharacter*, FPlayerStats> PlayerStats;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* BlueTeamWinSound;

	UPROPERTY(EditAnywhere, Category = "Sound")
	USoundBase* RedTeamWinSound;

	// TODO add background music

public:
	UFUNCTION( BlueprintCallable )
	int32 GetScore(ETeam Team) const;

	UFUNCTION( BlueprintCallable )
	TArray<FPlayerStats> GetSortedPlayerStats() const;

	UFUNCTION( BlueprintCallable )
	TMap<AGameCharacter*, FPlayerStats> GetPlayerStats() const;

	UFUNCTION( BlueprintCallable )
	void IncrementScore(ETeam Team, int32 Score);

	UFUNCTION( BlueprintCallable )
	void ResetScore(ETeam Team);

	UFUNCTION( BlueprintImplementableEvent )
	void OnGameOver(ETeam WinnerTeam);

	UFUNCTION( BlueprintCallable )
	void AnnounceWinnerTeam() const;

	UFUNCTION( BlueprintCallable )
	bool IsGameOver() const;

	ETeam CheckWinner() const;

	AApporelGameGameModeBase();

	void BeginPlay();
};
