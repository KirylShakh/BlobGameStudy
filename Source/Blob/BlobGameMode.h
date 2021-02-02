// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "Tile.h"

#include "BlobGameMode.generated.h"

UCLASS(MinimalAPI)
class ABlobGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ABlobGameMode();

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<ATile> TileClass;

	UPROPERTY(VisibleInstanceOnly, Category = "Runtime")
	FTransform NextSpawnPoint = FTransform(FVector(0.f, 0.f, -300.f));

	UPROPERTY(EditAnywhere, Category = "Config")
	int32 NumInitialTiles = 10;

	UPROPERTY(EditAnywhere, Category = "Config")
	float TileHeight = 200.f;

	void CreateInitialTiles();

	void AddTile();

protected:
	virtual void BeginPlay() override;

private:
	TArray<AActor*> Obstacles;
};



