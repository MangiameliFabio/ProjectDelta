// Fill out your copyright notice in the Description page of Project Settings.


#include "CombatState.h"

#include "IdleState.h"
#include "PlayerStateMachine.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "ProjectDelta/Player/PlayerCharacter.h"

void UCombatState::Start()
{
	Super::Start();

	TransitionToIdleCurrent = TransitionToIdle;

	STATE_MACHINE->Player->Combat = true;
	STATE_MACHINE->Player->bUseControllerRotationYaw = true;
	STATE_MACHINE->Player->GetCharacterMovement()->bOrientRotationToMovement = false;
	STATE_MACHINE->Player->FireRateCurrent = STATE_MACHINE->Player->FireRateAnimationDelay;
}

void UCombatState::End()
{
	Super::End();
	Fire = false;
	Zoomed = false;
	TransitionToIdleCurrent = TransitionToIdle;

	STATE_MACHINE->Player->Combat = false;
	STATE_MACHINE->Player->bUseControllerRotationYaw = false;
	STATE_MACHINE->Player->GetCharacterMovement()->bOrientRotationToMovement = true;
}

void UCombatState::Update(float DeltaTime)
{
	if (TransitionToIdleCurrent <= 0.f)
	{
		STATE_MACHINE->StateTransition(STATE_MACHINE->IdleState);
	}
	if (!Fire && !Zoomed)
	{
		TransitionToIdleCurrent -= DeltaTime;
	}
	else
	{
		TransitionToIdleCurrent = TransitionToIdle;
	}
	
	if (Fire)
	{
		if (STATE_MACHINE->Player->FireRateCurrent <= 0.f)
		{
			STATE_MACHINE->Player->FireGun();
			STATE_MACHINE->Player->FireRateCurrent = STATE_MACHINE->Player->FireRate;
		}
		else
		{
			STATE_MACHINE->Player->FireRateCurrent -= DeltaTime;
		}
	}
	else
	{
		STATE_MACHINE->Player->FireRateCurrent = STATE_MACHINE->Player->FireRateAnimationDelay;
	}
}

void UCombatState::HandleInput(EInputs Input)
{
	if (Input == EInputs::SECONDARY_ACTION_PRESSED)
	{
		STATE_MACHINE->Player->ZoomIn();
		STATE_MACHINE->Player->GetCharacterMovement()->MaxWalkSpeed = 200.f;
		Zoomed = true;
	}
	if (Input == EInputs::SECONDARY_ACTION_RELEASED)
	{
		STATE_MACHINE->Player->ZoomOut();
		STATE_MACHINE->Player->GetCharacterMovement()->MaxWalkSpeed = 600.f;
		Zoomed = false;
		if (!Fire)
		{
			STATE_MACHINE->StateTransition(STATE_MACHINE->IdleState);
		}
	}
	if (Input == EInputs::ACTION_PRESSED)
	{
		Fire = true;
	}
	if (Input == EInputs::ACTION_RELEASED)
	{
		Fire = false;
	}
}
