// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "BlobGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class BLOB_API UBlobGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	// Statistics
	float TimeTravelled = 0.f;
	float DistanceTravelled = 0.f;
	float MaxAccumulatedThickness = 0.f;
	float MaxAccumulatedSpeed = 0.f;
	int32 ObstaclesHitCount = 0;
	int32 DropletsCollectedCount = 0;

	UFUNCTION(BlueprintCallable)
	FString GetStatistics();

protected:
	TArray<FString> GetStats();
};
