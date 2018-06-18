// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

class AAbility;
class AArenaCharacter;
class USkeletalMeshComponent;

UCLASS( abstract )
class APPORELGAME_API AWeapon : public AActor
{
	GENERATED_BODY()
	
private:	
	// The primary attack of this Weapon, which will be executed when the owner pawn receives the PrimaryAttack input
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Setup")
	TSubclassOf<AAbility> PrimaryAttackClass;

	// The secondary attack of this Weapon, which will be executed when the owner pawn receives the SecondaryAttack input
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Setup")
	TSubclassOf<AAbility> SecondaryAttackClass;

	float LastTimeExecutedAbility;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

	UPROPERTY(EditDefaultsOnly, Category = "Primary Attack | Sound")
	USoundBase* SoundPrimaryAttack;

	UPROPERTY(EditDefaultsOnly, Category = "Secondary Attack | Sound")
	USoundBase* SoundSecondaryAttack;

	AAbility* PrimaryAttack;

	AAbility* SecondaryAttack;

public:	
	// Sets default values for this actor's properties
	AWeapon();
	
	UFUNCTION( BlueprintCallable )
	TSubclassOf<AAbility> GetPrimaryAttackClass() const;

	UFUNCTION( BlueprintCallable )
	TSubclassOf<AAbility> GetSecondaryAttackClass() const;

	UFUNCTION( BlueprintCallable )
	AAbility* GetPrimaryAttack();

	UFUNCTION( BlueprintCallable )
	AAbility* GetSecondaryAttack();

	UFUNCTION( BlueprintCallable )
	USkeletalMeshComponent* GetMeshComp() const;

	FTimerHandle TimerHandleAutoattack;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual bool ExecutePrimaryAttack();

	virtual void StartExecutingPrimaryAttack();

	// Calls ExecutePrimaryAttack returning nothing so it can be passed as a lambda to TimerHandleTimeBetweenFireAbility
	void TimerExecutePrimaryAttack();

	virtual void StopExecutingPrimaryAttack();

	virtual bool ExecuteSecondaryAttack();

	virtual void ExecuteImprove();
};
