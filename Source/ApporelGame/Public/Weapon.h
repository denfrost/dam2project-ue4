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
	TSubclassOf<AAbility> PrimaryAttack;

	// The secondary attack of this Weapon, which will be executed when the owner pawn receives the SecondaryAttack input
	UPROPERTY(EditDefaultsOnly, Category = "Weapon Setup")
	TSubclassOf<AAbility> SecondaryAttack;

	AArenaCharacter* OwningCharacter;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	USkeletalMeshComponent* MeshComp;

public:	
	// Sets default values for this actor's properties
	AWeapon();

	UFUNCTION( BlueprintCallable )
	AArenaCharacter* GetOwningCharacter() const;

	void SetOwningCharacter(AArenaCharacter* NewOwningCharacter);	

	UFUNCTION( BlueprintCallable )
	AAbility* GetPrimaryAttack() const;

	UFUNCTION( BlueprintCallable )
	AAbility* GetSecondaryAttack() const;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void ExecutePrimaryAttack();

	virtual void ExecuteSecondaryAttack();

	virtual void ExecuteImprove();
};
