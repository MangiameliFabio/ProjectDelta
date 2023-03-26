// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class ARifleProjectile;
class UCameraComponent;
class USpringArmComponent;
class UPlayerStateMachine;
UCLASS()
class PROJECTDELTA_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FireGun();
	
	UFUNCTION(BlueprintCallable)
	void FireProjectile();

	UFUNCTION(BlueprintCallable)
	FRotator GetAimRotation();
	
	void ZoomIn();
	void ZoomOut();

	UFUNCTION(BlueprintCallable)
	void SendInputToState(EInputs Input);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	void MoveForward(float AxisValue);
	void MoveRight(float AxisValue);

public:
	UPROPERTY(EditAnywhere)
	USpringArmComponent* SpringArm = nullptr;
	
	UPROPERTY(EditAnywhere, Category="Combat Stats")
	float FireRate = 0.5f;
	UPROPERTY(EditAnywhere, Category="Combat Stats")
	float FireRateAnimationDelay = 0.05f;
	float FireRateCurrent = FireRateAnimationDelay;

	UPROPERTY(BlueprintReadWrite)
	bool Combat = false;
	UPROPERTY(BlueprintReadWrite)
	bool Idle = false;

private:
	UPROPERTY(EditAnywhere, Category="Particles")
	UParticleSystem* MuzzleFlash = nullptr;
	UPROPERTY(EditAnywhere, Category="Particles")
	UParticleSystem* HitEffect = nullptr;
	UPROPERTY(EditAnywhere)
	UCameraComponent* Camera = nullptr;

	UPROPERTY(EditAnywhere)
	UPlayerStateMachine* StateMachine = nullptr;
	
	UPROPERTY(EditDefaultsOnly,Category="Projectile")
	TSubclassOf<ARifleProjectile> RifleProjectile;
};
