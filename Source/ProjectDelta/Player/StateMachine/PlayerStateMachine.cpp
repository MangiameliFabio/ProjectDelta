// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerStateMachine.h"

#include "CombatState.h"
#include "IdleState.h"
#include "ProjectDelta/Player/PlayerCharacter.h"

// Sets default values for this component's properties
UPlayerStateMachine::UPlayerStateMachine()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UPlayerStateMachine::BeginPlay()
{
	Super::BeginPlay();

	Player = Cast<APlayerCharacter>(GetOwner());

	IdleState = NewObject<UIdleState>();
	IdleState->Init(this);
	CombatState = NewObject<UCombatState>();
	CombatState->Init(this);

	CurrentState = IdleState;
	CurrentState->Start();
}


// Called every frame
void UPlayerStateMachine::TickComponent(float DeltaTime, ELevelTick TickType,
                                        FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	CurrentState->Update(DeltaTime);
}
