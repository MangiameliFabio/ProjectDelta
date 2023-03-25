#pragma once

#include "CoreMinimal.h"
#include "ProjectDelta/BaseClasses/State.h"
#include "IdleState.generated.h"

UCLASS()
class PROJECTDELTA_API UIdleState final : public UState
{
	GENERATED_BODY()
	
public:
	virtual void Start() override;
	virtual void End() override;
	virtual void Update(float DeltaTime) override;
	virtual void HandleInput(EInputs Input) override;
};
