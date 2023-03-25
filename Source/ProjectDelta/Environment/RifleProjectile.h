// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "NiagaraComponent.h"
#include "RifleProjectile.generated.h"

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

public:
	UPROPERTY(EditDefaultsOnly)
	UNiagaraComponent* ProjectileTrail = nullptr;

	FVector FlightDirection = FVector::Zero();

	UPROPERTY(EditAnywhere)
	float ProjectileSpeed = 2000.f;
};
