// Fill out your copyright notice in the Description page of Project Settings.


#include "BlobGameInstance.h"

FString UBlobGameInstance::GetStatistics()
{
    TArray<FString> Messages = GetStats();
    FString Result = "";
    for (int i = Messages.Num() - 1; i >= 0; i--)
    {
        Result += Messages[i] + "\r\n";
    }
    return Result;
}

void UBlobGameInstance::ResetStatistics()
{
    TimeTravelled = 0.f;
    DistanceTravelled = 0.f;
    MaxAccumulatedThickness = 0.f;
    MaxAccumulatedSpeed = 0.f;
    ObstaclesHitCount = 0;
    DropletsCollectedCount = 0;
}

TArray<FString> UBlobGameInstance::GetStats()
{
    TArray<FString> Messages;
    Messages.Add("Time travelled: " + FString::SanitizeFloat(TimeTravelled));
    Messages.Add("Distance travelled: " + FString::SanitizeFloat(DistanceTravelled));
    Messages.Add("Maximum accumulated thickness: " + FString::SanitizeFloat(MaxAccumulatedThickness));
    Messages.Add("Maximum accumulated speed: " + FString::SanitizeFloat(MaxAccumulatedSpeed));
    Messages.Add("Obstacles hit count: " + FString::FromInt(ObstaclesHitCount));
    Messages.Add("Droplets collected count: " + FString::FromInt(DropletsCollectedCount));

    return Messages;
}
