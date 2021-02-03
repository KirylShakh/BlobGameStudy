// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "BlobGameInstance.h"
#include "BlobPiecePawn.h"
#include "BlobPawn.h"
#include "Obstacle.h"

// Sets default values
AObstacle::AObstacle()
{
	Wrapper = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Wrapper;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);

	CapsuleCmp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleCmp->SetRelativeLocation(FVector(0.f, 0.f, -10.f));
	CapsuleCmp->SetRelativeScale3D(FVector(2.f, 1.5f, 1.25f));
	CapsuleCmp->SetupAttachment(Mesh);
}

void AObstacle::BeginPlay()
{
	Super::BeginPlay();

	CapsuleCmp->OnComponentBeginOverlap.AddDynamic(this, &AObstacle::OnTrigger);
}

void AObstacle::OnTrigger_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABlobPawn* Blob = Cast<ABlobPawn>(OtherActor);
	if (Blob && bCollideWithBlob)
	{
		Blob->BlobGameInstance->ObstaclesHitCount++;

		Blob->UpdateThickness(-(Blob->Thickness / 2.f));
		Blob->MoveSpeed = FGenericPlatformMath::Max(Blob->MoveSpeed / 2.f, Blob->MinMoveSpeed);

		// Spawn blob piece
		FActorSpawnParameters SpawnParameters;
		SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
		const FTransform SpawnTransform = Blob->GetTransform();
		ABlobPiecePawn* BlobPiece = GetWorld()->SpawnActor<ABlobPiecePawn>(BlopPieceClass, SpawnTransform, SpawnParameters);
		if (BlobPiece)
		{
			BlobPiece->SetupMove(Blob->MoveSpeed, Blob->Thickness);
		}

		bCollideWithBlob = false;
	}
}
