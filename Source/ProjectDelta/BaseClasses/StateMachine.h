// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "StateMachine.generated.h"

class UCombatState;
class APlayerCharacter;
class UState;
class UIdleState;
UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class PROJECTDELTA_API UStateMachine : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UStateMachine();
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	void StateTransition(UState* NewState);

	UPROPERTY()
	UState* CurrentState  = nullptr;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;
};
