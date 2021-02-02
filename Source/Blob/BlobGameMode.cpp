// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlobGameMode.h"
#include "BlobPawn.h"

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
		NextSpawnPoint = FTransform(FVector(0.f, 0.f, NextSpawnPoint.GetTranslation().Z - TileHeight));
	}
}
