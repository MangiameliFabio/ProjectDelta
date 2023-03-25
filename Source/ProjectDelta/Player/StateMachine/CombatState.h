// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ProjectDelta/BaseClasses/State.h"
#include "CombatState.generated.h"

/**
 * 
 */
UCLASS()
class PROJECTDELTA_API UCombatState : public UState
{
	GENERATED_BODY()

	virtual void Start() override;
	virtual void End() override;
	virtual void Update(float DeltaTime) override;
	virtual void HandleInput(EInputs Input) override;
public:
	bool Fire = false;
	bool Zoomed = false;

private:
	float TransitionToIdle = 1.f;
	float TransitionToIdleCurrent = TransitionToIdle;
};
