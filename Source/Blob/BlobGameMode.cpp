// Copyright Epic Games, Inc. All Rights Reserved.

#include "BlobGameMode.h"
#include "BlobPawn.h"

ABlobGameMode::ABlobGameMode()
{
	// set default pawn class to our character class
	DefaultPawnClass = ABlobPawn::StaticClass();
}

