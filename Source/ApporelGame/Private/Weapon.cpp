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

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();

	if (PrimaryAttackClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The weapon %s doesn't have a primary attack!"), *GetName());
	}

	if (SecondaryAttackClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The weapon %s doesn't have a secondary attack!"), *GetName());
	}
	PrimaryAttack = GetWorld()->SpawnActor<AAbility>(PrimaryAttackClass.GetDefaultObject()->GetClass());
	PrimaryAttack->SetOwner(this);

	SecondaryAttack = GetWorld()->SpawnActor<AAbility>(SecondaryAttackClass.GetDefaultObject()->GetClass());
	SecondaryAttack->SetOwner(this);
}

TSubclassOf<AAbility> AWeapon::GetPrimaryAttackClass() const
{
	return PrimaryAttackClass;
}

TSubclassOf<AAbility> AWeapon::GetSecondaryAttackClass() const
{
	return SecondaryAttackClass;
}

USkeletalMeshComponent* AWeapon::GetMeshComp() const
{
	return MeshComp;
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

bool AWeapon::ExecutePrimaryAttack()
{
	if (PrimaryAttackClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The weapon %s doesn't have a primary attack!"), *GetName());
		return false;
	}

	AArenaCharacter* Owner = Cast<AArenaCharacter>(GetOwner());
	if (!Owner)
	{
		UE_LOG(LogTemp, Error, TEXT("The weapon: %s has no Owner"), *this->GetName());
		return false;
	}
	if (!PrimaryAttack->InternalExecute(Owner))
	{
		return false;
	}
	LastTimeExecutedAbility = GetWorld()->TimeSeconds;
	return true;
}

AAbility* AWeapon::GetPrimaryAttack()
{
	return PrimaryAttack;
}

AAbility* AWeapon::GetSecondaryAttack()
{
	return SecondaryAttack;
}

void AWeapon::StartExecutingPrimaryAttack()
{
	float FirstDelay = FMath::Max(LastTimeExecutedAbility + GetPrimaryAttack()->GetCooldown() - GetWorld()->TimeSeconds, 0.f);

	GetWorldTimerManager().SetTimer(TimerHandle_TimeBetweenFireAbility, this, &AWeapon::CheckExecutePrimaryAttackCanBeExecuted, GetPrimaryAttack()->GetCooldown(), true, FirstDelay);
}

void AWeapon::CheckExecutePrimaryAttackCanBeExecuted()
{
	if (!ExecutePrimaryAttack()) return;
}

void AWeapon::StopExecutingPrimaryAttack()
{
	GetWorldTimerManager().ClearTimer(TimerHandle_TimeBetweenFireAbility);
}

bool AWeapon::ExecuteSecondaryAttack()
{
	if (SecondaryAttackClass == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The weapon %s doesn't have a secondary attack!"), *GetName());
		return false;
	}
	AArenaCharacter* Owner = Cast<AArenaCharacter>(GetOwner());
	if (!Owner)
		return false;

	if (!SecondaryAttack->InternalExecute(Owner))
	{
		return false;
	}
	return true;
}

void AWeapon::ExecuteImprove()
{
	// TODO implement
}

