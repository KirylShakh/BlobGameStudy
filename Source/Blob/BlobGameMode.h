// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"

#include "BlobGameMode.generated.h"

class ATile;
class AObstacle;

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

	UPROPERTY(EditAnywhere, Category = "Config")
	TSubclassOf<AObstacle> ObstacleClass;

	UPROPERTY(EditAnywhere, Category = "Config")
	float MaxObstaclesPerTile = 10.f;

	UPROPERTY(EditAnywhere, Category = "Config")
	float ObstacleWidth = 100.f;

	UPROPERTY(EditAnywhere, Category = "Config")
	float LeftBorder = -1000.f;
	
	UPROPERTY(EditAnywhere, Category = "Config")
	float RightBorder = 1000.f;

	void CreateObstacles(ATile* Tile);

	AObstacle* CreateObstacle(float StartY);

protected:
	virtual void BeginPlay() override;
};



