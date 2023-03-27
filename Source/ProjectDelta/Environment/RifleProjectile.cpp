// Fill out your copyright notice in the Description page of Project Settings.


#include "RifleProjectile.h"

#include "Components/SphereComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"
#include "ProjectDelta/Log.h"


// Sets default values
ARifleProjectile::ARifleProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	CollisionSphere = CreateDefaultSubobject<USphereComponent>("CollisionSphere");
	RootComponent = CollisionSphere;

	ProjectileTrail = CreateDefaultSubobject<UParticleSystemComponent>("ProjectileTrail");
	ProjectileTrail->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void ARifleProjectile::BeginPlay()
{
	Super::BeginPlay();

	CollisionSphere->OnComponentBeginOverlap.AddDynamic(this, &ARifleProjectile::OnHit);
}

void ARifleProjectile::OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                             UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
                             const FHitResult& SweepResult)
{
	ProjectileTrail->Deactivate();
	if (!HitWorldEffect) { return; }
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), HitWorldEffect, GetActorLocation());
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
