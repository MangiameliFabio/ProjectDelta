#pragma once

#include "CoreMinimal.h"
#include "ProjectDelta/Enums.h"
#include "StateMachine.h"
#include "State.generated.h"

UCLASS()
class PROJECTDELTA_API UState : public UObject
{
	GENERATED_BODY()

public:
	virtual void Init(UStateMachine* NewStateMachine);
	virtual void Start();
	virtual void End();
	virtual void Update(float DeltaTime);
	virtual void HandleInput(EInputs Input);

	UPROPERTY()
	UStateMachine* StateMachine = nullptr;
};

inline void UState::Init(UStateMachine* NewStateMachine)
{
	StateMachine = NewStateMachine;
}

inline void UState::Start()
{
}

inline void UState::End()
{
}

inline void UState::Update(float DeltaTime)
{
}

inline void UState::HandleInput(EInputs Input)
{
}
