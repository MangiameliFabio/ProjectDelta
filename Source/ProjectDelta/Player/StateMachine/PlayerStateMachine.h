// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectDelta/BaseClasses/StateMachine.h"
#include "PlayerStateMachine.generated.h"

#define STATE_MACHINE Cast<UPlayerStateMachine>(StateMachine)

class UCombatState;
class APlayerCharacter;
class UState;
class UIdleState;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTDELTA_API UPlayerStateMachine : public UStateMachine
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UPlayerStateMachine();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UPROPERTY()
	APlayerCharacter* Player = nullptr;
	UPROPERTY()
	UIdleState* IdleState = nullptr;
	UPROPERTY()
	UCombatState* CombatState = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
