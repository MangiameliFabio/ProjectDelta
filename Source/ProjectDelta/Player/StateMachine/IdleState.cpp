#include "IdleState.h"

#include "CombatState.h"
#include "PlayerStateMachine.h"
#include "ProjectDelta/Player/PlayerCharacter.h"

void UIdleState::Start()
{
	if (!StateMachine) { return; }
	STATE_MACHINE->Player->Idle = true;
}

void UIdleState::HandleInput(EInputs Input)
{
	Super::HandleInput(Input);

	if (Input == EInputs::SECONDARY_ACTION_PRESSED)
	{
		STATE_MACHINE->StateTransition(STATE_MACHINE->CombatState);
		STATE_MACHINE->Player->ZoomIn();
		STATE_MACHINE->CombatState->Zoomed = true;
	}
	if (Input == EInputs::ACTION_PRESSED)
	{
		STATE_MACHINE->StateTransition(STATE_MACHINE->CombatState);
		STATE_MACHINE->CombatState->Fire = true;
	}
}

void UIdleState::End()
{
	if (!StateMachine) { return; }
	STATE_MACHINE->Player->Idle = false;
}

void UIdleState::Update(float DeltaTime)
{
}
