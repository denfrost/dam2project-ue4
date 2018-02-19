// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Weapon.generated.h"

UCLASS( abstract )
class ARCHITECTURETEST_API AWeapon : public AActor
{
	GENERATED_BODY()
	
private:	

	UPROPERTY( EditAnywhere )
	int32 Damage;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Sets default values for this actor's properties
	AWeapon();

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	inline int32 GetDamage() { return Damage; }
	inline void SetDamage(int32 Damage) { this->Damage = Damage;  }

	virtual int PrimaryAttack();

	virtual int SecondaryAttack();

	virtual int Improve();
};
