#pragma once
using namespace ELogVerbosity;

class FLog
{
public:
	static void Print(const bool& BoolToLog, const FString Message = "")
	{
		if (BoolToLog)
		{
			UE_LOG(LogTemp, Warning, TEXT("%s true"), *Message)
		}
		else
		{
			UE_LOG(LogTemp, Warning, TEXT("%s false"), *Message);
		}
	}

	static void Print(const float& FloatToLog, const FString Message = "")
	{
		UE_LOG(LogTemp, Warning, TEXT("%s %f"), *Message, FloatToLog);
	}

	static void Print(const FVector& VectorToLog, const FString Message = "")
	{
		UE_LOG(LogTemp, Warning, TEXT("%s %s"), *Message, *VectorToLog.ToString());
	}

	static void Print(const AActor& ActorToLog, const FString Message = "")
	{
		UE_LOG(LogTemp, Warning, TEXT("%s %s"), *Message, *ActorToLog.GetActorNameOrLabel());
	}

	static void Print(const FString StringToLog)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s"), *StringToLog);
	}
};
