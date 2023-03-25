#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Enums.generated.h"

UENUM(BlueprintType)
enum class EInputs : uint8
{
	ACTION_PRESSED,
	ACTION_RELEASED,
	SECONDARY_ACTION_PRESSED,
	SECONDARY_ACTION_RELEASED,
};
