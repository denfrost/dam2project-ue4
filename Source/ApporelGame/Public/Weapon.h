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

	AAbility* PrimaryAttack;

	AAbility* SecondaryAttack;

public:	
	// Sets default values for this actor's properties
	AWeapon();
	
	UFUNCTION( BlueprintCallable )
	AAbility* GetPrimaryAttackClass() const;

	UFUNCTION( BlueprintCallable )
	AAbility* GetSecondaryAttackClass() const;

	UFUNCTION(BlueprintCallable)
	USkeletalMeshComponent* GetMeshComp() const;

	FTimerHandle TimerHandle_TimeBetweenFireAbility;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ExecutePrimaryAttack();

	AAbility* GetPrimaryAttack();

	AAbility* GetSecondaryAttack();

	virtual void StartExecutingPrimaryAttack();

	virtual void StopExecutingPrimaryAttack();

	virtual void ExecuteSecondaryAttack();

	virtual void ExecuteImprove();
};
