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

	if (Weapon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a weapon!"), *GetName());
		return;
	}
	SetWeapon(Weapon); // To call Weapon->SetOwningCharacter(this)

	if (GetWeapon()->GetPrimaryAttack() == nullptr || GetWeapon()->GetSecondaryAttack() == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have some ability!"), *GetName());
		return;
	}

	// Set Weapon attacks last use to -Cooldown to be able to cast them instantly at the beginning of the match
	GetWeapon()->GetPrimaryAttack()->SetLastUse(-GetWeapon()->GetPrimaryAttack()->GetCooldown());
	GetWeapon()->GetSecondaryAttack()->SetLastUse(-GetWeapon()->GetSecondaryAttack()->GetCooldown());

	// Spawn the Weapon and attach it to the player
	auto Spawned = GetWorld()->SpawnActor(GetWeapon()->GetClass());

	Spawned->AttachToComponent(GetMesh(), FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true), GRAB_POINT_SOCKET_NAME);
}

AWeapon* AArenaCharacter::GetWeapon() const
{
	ensure(Weapon != nullptr);
	return Weapon.GetDefaultObject();
}

void AArenaCharacter::SetWeapon(TSubclassOf<AWeapon> NewWeapon)
{
	Weapon = NewWeapon;
	NewWeapon.GetDefaultObject()->SetOwningCharacter(this);
}

void AArenaCharacter::SetupPlayerInputComponent(UInputComponent * PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction("PrimaryAttack", IE_Pressed, this, &AArenaCharacter::PrimaryAttack);
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
	ensure(Weapon != nullptr);
	return GetWeapon()->GetPrimaryAttack();
}

AAbility* AArenaCharacter::GetSecondaryAttack() const
{
	ensure(Weapon != nullptr);
	return GetWeapon()->GetSecondaryAttack();
}

void AArenaCharacter::PrimaryAttack()
{
	if (Weapon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a weapon!"), *GetName());
		return;
	}
	return Weapon.GetDefaultObject()->ExecutePrimaryAttack();
}

void AArenaCharacter::SecondaryAttack()
{
	if (Weapon == nullptr)
	{
		UE_LOG(LogTemp, Error, TEXT("The character %s doesn't have a weapon!"), *GetName());
		return;
	}
	return Weapon.GetDefaultObject()->ExecuteSecondaryAttack();
}

void AArenaCharacter::Improve()
{
	return Weapon.GetDefaultObject()->ExecuteImprove();
}

FVector AArenaCharacter::GetPawnViewLocation() const
{
	if (CameraComp)
	{
		return CameraComp->GetComponentLocation();
	}
	return Super::GetPawnViewLocation();
}
