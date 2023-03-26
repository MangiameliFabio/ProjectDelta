// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleProjectile.h"

#include "Particles/ParticleSystem.h"


// Sets default values
ARifleProjectile::ARifleProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	Root = CreateDefaultSubobject<USceneComponent>("Root");
	RootComponent = Root;
}

// Called when the game starts or when spawned
void ARifleProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARifleProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	SetActorLocation(GetActorLocation() + FlightDirection * ProjectileSpeed * DeltaTime);
}

void ARifleProjectile::Init(FVector NewFlightDirection)
{
	FlightDirection = NewFlightDirection;
}
