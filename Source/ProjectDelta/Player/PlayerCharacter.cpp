// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Blueprint/UserWidget.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "ProjectDelta/Log.h"
#include "ProjectDelta/BaseClasses/State.h"
#include "ProjectDelta/Environment/RifleProjectile.h"
#include "StateMachine/PlayerStateMachine.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	SpringArm = CreateDefaultSubobject<USpringArmComponent>("SpringArm");
	SpringArm->SetupAttachment(RootComponent);
	Camera = CreateDefaultSubobject<UCameraComponent>("Camera");
	Camera->SetupAttachment(SpringArm);

	StateMachine = CreateDefaultSubobject<UPlayerStateMachine>(TEXT("StateMachine"));
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//
	// DrawDebugLine(GetWorld(), GetMesh()->GetSocketLocation("Muzzle_01"),
	//               GetMesh()->GetSocketLocation("Muzzle_01") + GetMesh()->GetSocketTransform("Muzzle_01").GetRotation().GetForwardVector() +
	//               10000.f, FColor::Red);
}

void APlayerCharacter::MoveForward(float AxisValue)
{
	const FRotator Rotator(0, 0, GetControlRotation().Yaw);
	const FVector ForwardVector = FRotationMatrix(Rotator).GetScaledAxis(EAxis::X);


	AddMovementInput(ForwardVector, AxisValue);
}

void APlayerCharacter::MoveRight(float AxisValue)
{
	const FRotator Rotator(0, 0, GetControlRotation().Yaw);
	const FVector RightVector = FRotationMatrix(Rotator).GetScaledAxis(EAxis::Y) * -1;


	AddMovementInput(RightVector, AxisValue);
}

void APlayerCharacter::FireProjectile()
{
	//Check for Particles and spawn them
	if (!MuzzleFlash)
	{
		UE_LOG(LogTemp, Warning, TEXT("No muzzle particle in Player"));
		return;
	}
	UGameplayStatics::SpawnEmitterAttached(MuzzleFlash, GetMesh(), TEXT("Muzzle_01"));

	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	FVector SpawnLocation = GetMesh()->GetSocketLocation("Muzzle_01");
	FRotator SpawnRotation = GetMesh()->GetSocketRotation("Muzzle_01");

	ARifleProjectile* NewProjectile = GetWorld()->SpawnActor<ARifleProjectile>(
		RifleProjectile, SpawnLocation, SpawnRotation, SpawnParams);

	NewProjectile->Init(SpawnRotation.Vector());
}

FRotator APlayerCharacter::GetAimRotation()
{
	FRotator AimRotation(0, 0, 0);
	if (!GetController()) { return AimRotation; }

	FVector Location;
	FRotator Rotation;
	GetController()->GetPlayerViewPoint(Location, Rotation);

	FHitResult Hit;

	FVector AimVector = Location + Rotation.Vector() * 100000.f - GetMesh()->GetSocketLocation("Weapon_R");

	if (GetPointedHit(Hit, Location, Rotation))
	{
		AimVector = Hit.Location - GetMesh()->GetSocketLocation("Weapon_R");
	}
	AimVector.Normalize();

	return AimRotation = AimVector.Rotation();
}

bool APlayerCharacter::GetPointedHit(FHitResult& Hit, FVector& Location, FRotator& Rotation)
{
	// Set up the trace parameters
	FCollisionQueryParams TraceParams(FName(TEXT("MyTrace")), true, this);

	const FVector End = Location + Rotation.Vector() * 100000.f;
	
	return GetWorld()->LineTraceSingleByChannel(Hit, Location, End, ECC_GameTraceChannel2, TraceParams);
}

void APlayerCharacter::ZoomIn()
{
	SpringArm->TargetArmLength = 150.f;
}

void APlayerCharacter::ZoomOut()
{
	SpringArm->TargetArmLength = 300.f;
}

void APlayerCharacter::SendInputToState(EInputs Input)
{
	StateMachine->CurrentState->HandleInput(Input);
}
