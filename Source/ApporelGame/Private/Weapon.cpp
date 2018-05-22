// Fill out your copyright notice in the Description page of Project Settings.

#include "Weapon.h"
#include "ArenaCharacter.h"
#include "Ability.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	MeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("MeshComp"));
	RootComponent = MeshComp;
}

AArenaCharacter* AWeapon::GetOwningCharacter() const
{
	return OwningCharacter;
}

void AWeapon::SetOwningCharacter(AArenaCharacter* NewOwningCharacter)
{
	OwningCharacter = NewOwningCharacter;
	SetOwner(NewOwningCharacter);
}

AAbility* AWeapon::GetPrimaryAttack() const
{
	return PrimaryAttack.GetDefaultObject();
}

AAbility* AWeapon::GetSecondaryAttack() const
{
	return SecondaryAttack.GetDefaultObject();
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (PrimaryAttack == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The weapon %s doesn't have a primary attack!"), *GetName());
	}

	if (SecondaryAttack == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The weapon %s doesn't have a secondary attack!"), *GetName());
	}
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::ExecutePrimaryAttack()
{
	if (PrimaryAttack == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The weapon %s doesn't have a primary attack!"), *GetName());
		return;
	}
	AArenaCharacter* Owner = Cast<AArenaCharacter>(GetOwner());
	
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("The weapon has no owner RIP"));
		return;
	}
	PrimaryAttack.GetDefaultObject()->InternalExecute(Owner);
}

void AWeapon::ExecuteSecondaryAttack()
{
	if (SecondaryAttack == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The weapon %s doesn't have a secondary attack!"), *GetName());
		return;
	}
	AArenaCharacter* Owner = Cast<AArenaCharacter>(GetOwner());
	if (!Owner)
		return;
	SecondaryAttack.GetDefaultObject()->InternalExecute(Owner);
}

void AWeapon::ExecuteImprove()
{
	// TODO implement
}

