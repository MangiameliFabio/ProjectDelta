// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "RifleProjectile.generated.h"

class USphereComponent;
UCLASS()
class PROJECTDELTA_API ARifleProjectile : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ARifleProjectile();
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void Init(FVector NewFlightDirection);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	UFUNCTION()
	void OnHit(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

public:
	UPROPERTY(EditDefaultsOnly)
	USphereComponent* CollisionSphere = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UParticleSystemComponent* ProjectileTrail = nullptr;
	UPROPERTY(EditDefaultsOnly)
	UParticleSystem* HitWorldEffect = nullptr;

	FVector FlightDirection = FVector::Zero();

	UPROPERTY(EditAnywhere)
	float ProjectileSpeed = 2000.f;
};
