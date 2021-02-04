// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlobGameMode.h"
#include "BlobPawn.h"
#include "Tile.h"
#include "Obstacle.h"
#include "Droplet.h"

ABlobGameMode::ABlobGameMode()
{
	PrimaryActorTick.bCanEverTick = true;
}

void ABlobGameMode::BeginPlay()
{
	Super::BeginPlay();

	CreateInitialTiles();
}

void ABlobGameMode::CreateInitialTiles()
{
	for (int i = 0; i < NumInitialTiles; i++)
	{
		AddTile();
	}
}

void ABlobGameMode::AddTile()
{
	ATile* Tile = GetWorld()->SpawnActor<ATile>(TileClass, NextSpawnPoint);
	if (Tile)
	{
		CreatePlacebles(Tile);
		NextSpawnPoint = FTransform(FVector(0.f, 0.f, NextSpawnPoint.GetTranslation().Z - TileHeight));
	}
}

void ABlobGameMode::CreatePlacebles(ATile* Tile)
{
	float RandDeltaY = FMath::FRandRange(0.f, ObstacleWidth);
	float Y = LeftBorder + RandDeltaY + ObstacleWidth / 2.f;
	float MaxY = RightBorder - ObstacleWidth / 2.f;

	// Make a list of potential starting Y-positions for obstacles
	TArray<float> PotentialSpawnPoints;
	while (Y <= MaxY)
	{
		PotentialSpawnPoints.Add(Y);
		Y += ObstacleWidth;
	}
	
	int32 NumObstacles = FMath::FloorToInt(FMath::FRandRange(0.f, MaxObstaclesPerTile));
	for (int32 i = 0; i < NumObstacles; i++)
	{
		int32 Index = FMath::FloorToInt(FMath::FRandRange(0.f, (float)PotentialSpawnPoints.Num() - .6f));
		Tile->AddPlaceble(CreateObstacle(PotentialSpawnPoints[Index]));
		PotentialSpawnPoints.RemoveAt(Index);
	}

	int32 NumDroplets = FMath::FloorToInt(FMath::FRandRange(0.f, MaxDropletsPerTile));
	for (int32 i = 0; i < NumDroplets; i++)
	{
		int32 Index = FMath::FloorToInt(FMath::FRandRange(0.f, (float)PotentialSpawnPoints.Num() - .6f));
		Tile->AddPlaceble(CreateDroplet(PotentialSpawnPoints[Index]));
		PotentialSpawnPoints.RemoveAt(Index);
	}
}

AObstacle* ABlobGameMode::CreateObstacle(float SpawnY)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	float SpawnZ = FMath::FRandRange(NextSpawnPoint.GetTranslation().Z, NextSpawnPoint.GetTranslation().Z + TileHeight);
	const FTransform SpawnTransform = FTransform(FVector(0.f, SpawnY, SpawnZ));
	return GetWorld()->SpawnActor<AObstacle>(ObstacleClass, SpawnTransform, SpawnParameters);
}

ADroplet* ABlobGameMode::CreateDroplet(float SpawnY)
{
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	float SpawnZ = FMath::FRandRange(NextSpawnPoint.GetTranslation().Z, NextSpawnPoint.GetTranslation().Z + TileHeight);
	const FTransform SpawnTransform = FTransform(FVector(0.f, SpawnY, SpawnZ));
	return GetWorld()->SpawnActor<ADroplet>(DropletClass, SpawnTransform, SpawnParameters);
}
