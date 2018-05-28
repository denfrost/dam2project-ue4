// Fill out your copyright notice in the Description page of Project Settings.

#include "ArenaCharacter.h"
#include "Weapon.h"
#include "Ability.h"
#include "Camera/CameraComponent.h"
#include "GameFramework//SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"

AArenaCharacter::AArenaCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SprinArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArmComp"));
	SprinArmComp->bUsePawnControlRotation = true;
	SprinArmComp->SetupAttachment(RootComponent);

	GetMovementComponent()->GetNavAgentPropertiesRef().bCanCrouch = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComp"));
	CameraComp->SetupAttachment(SprinArmComp);
}

// Called when the game starts or when spawned
void AArenaCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (WeaponToSpawn == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a weapon!"), *GetName());
		return;
	}

	// Spawn the Weapon and attach it to the player
	CurrentWeapon = GetWorld()->SpawnActor<AWeapon>(WeaponToSpawn.GetDefaultObject()->GetClass());
	CurrentWeapon->SetOwner(this);

	if (!CurrentWeapon)
	{
		UE_LOG(LogTemp, Error, TEXT("Not Current Weapon Available"));
		return;
	}

	CurrentWeapon->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), GRAB_POINT_SOCKET_NAME);

	//TODO Refactor this
	if (CurrentWeapon->GetPrimaryAttackClass() == nullptr || CurrentWeapon->GetSecondaryAttackClass() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have some ability!"), *GetName());
		return;
	}

	//TODO extracts to a method
	// Set Weapon attacks last use to -Cooldown to be able to cast them instantly at the beginning of the match
	CurrentWeapon->GetPrimaryAttackClass()->SetLastUse(-CurrentWeapon->GetPrimaryAttackClass()->GetCooldown());
	CurrentWeapon->GetSecondaryAttackClass()->SetLastUse(-CurrentWeapon->GetSecondaryAttackClass()->GetCooldown());
}

TSubclassOf<AWeapon> AArenaCharacter::GetWeaponToSpawn() const
{
	ensure(WeaponToSpawn != nullptr);
	return WeaponToSpawn;
}

void AArenaCharacter::SetWeaponToSpawn(TSubclassOf<AWeapon> NewWeaponToSpawn)
{
	WeaponToSpawn = NewWeaponToSpawn;
}

AWeapon* AArenaCharacter::GetCurrentWeapon()
{
	ensure(CurrentWeapon != nullptr);
	return CurrentWeapon;
}

void AArenaCharacter::SetCurrentWeapon(AWeapon* NewCurrentWeapon)
{
	CurrentWeapon = NewCurrentWeapon;
	NewCurrentWeapon->SetOwner(this);
}

void AArenaCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AArenaCharacter::StartPrimaryAttack);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Released, this, &AArenaCharacter::StopPrimaryAttack);

	PlayerInputComponent->BindAction("SecondaryAttack", IE_Pressed, this, &AArenaCharacter::SecondaryAttack);

	//Setup basic movement
	PlayerInputComponent->BindAxis("MoveForward", this, &AArenaCharacter::MoveForward);
	PlayerInputComponent->BindAxis("MoveRight", this, &AArenaCharacter::MoveRight);

	PlayerInputComponent->BindAxis("LookUp", this, &AArenaCharacter::AddControllerPitchInput);
	PlayerInputComponent->BindAxis("Turn", this, &AArenaCharacter::AddControllerYawInput);

	PlayerInputComponent->BindAction("Crouch", IE_Pressed, this, &AArenaCharacter::BeginCrouch);
	PlayerInputComponent->BindAction("Crouch", IE_Released, this, &AArenaCharacter::EndCrouch);

	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
}

void AArenaCharacter::MoveForward(float value)
{
	AddMovementInput(GetActorForwardVector() * value);
}

void AArenaCharacter::MoveRight(float value)
{
	AddMovementInput(GetActorRightVector() * value);
}

void AArenaCharacter::BeginCrouch()
{
	Crouch();
}

void AArenaCharacter::EndCrouch()
{
	UnCrouch();
}

AAbility* AArenaCharacter::GetPrimaryAttack() const
{
	ensure(CurrentWeapon != nullptr);
	return CurrentWeapon->GetPrimaryAttackClass();
}

AAbility* AArenaCharacter::GetSecondaryAttack() const
{
	ensure(CurrentWeapon != nullptr);
	return CurrentWeapon->GetSecondaryAttackClass();
}

void AArenaCharacter::StartPrimaryAttack()
{
	if (CurrentWeapon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a weapon!"), *GetName());
		return;
	}
	CurrentWeapon->StartExecutingPrimaryAttack();
}

void AArenaCharacter::StopPrimaryAttack()
{
	if (CurrentWeapon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a weapon!"), *GetName());
		return;
	}
	CurrentWeapon->StopExecutingPrimaryAttack();
}


void AArenaCharacter::SecondaryAttack()
{
	if (CurrentWeapon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a weapon!"), *GetName());
		return;
	}
	CurrentWeapon->ExecuteSecondaryAttack();
}

void AArenaCharacter::Improve()
{
	return CurrentWeapon->ExecuteImprove();
}

FVector AArenaCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}
