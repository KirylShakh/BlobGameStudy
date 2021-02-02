// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "BlobGameMode.generated.h"

UCLASS(MinimalAPI)
class ABlobGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABlobGameMode();

protected:
	virtual void BeginPlay() override;

private:
	TArray<AActor*> Obstacles;
};



