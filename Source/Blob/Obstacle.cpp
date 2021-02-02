// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

#include "Obstacle.h"

// Sets default values
AObstacle::AObstacle()
{
	Wrapper = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Wrapper;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	// Mesh->SetCollisionProfileName(TEXT("Pawn"));
	Mesh->SetupAttachment(RootComponent);
}
