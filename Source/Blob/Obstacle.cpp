// Fill out your copyright notice in the Description page of Project Settings.


#include "Obstacle.h"
#include "BlobGameInstance.h"
#include "BlobPawn.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

// Sets default values
AObstacle::AObstacle()
{
	CapsuleCmp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleCmp->SetRelativeScale3D(FVector(.3f, .3f, 1.f));
	SetRootComponent(CapsuleCmp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetRelativeLocation(FVector(0.f, 0.f, 10.f));
	Mesh->SetRelativeScale3D(FVector(1.3f, 1.3f, .8f));
	Mesh->SetupAttachment(CapsuleCmp);
}

void AObstacle::OnHit(ABlobPawn* Blob)
{
	if (!bMetWithBlob)
	{
		Blob->BlobGameInstance->ObstaclesHitCount++;
		bMetWithBlob = true;
	}
}
