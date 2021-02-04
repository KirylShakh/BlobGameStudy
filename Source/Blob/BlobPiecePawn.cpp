// Fill out your copyright notice in the Description page of Project Settings.


#include "BlobPiecePawn.h"
#include "BlobPawnMovementComponent.h"

// Sets default values
ABlobPiecePawn::ABlobPiecePawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Wrapper = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Wrapper;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetCollisionProfileName(TEXT("Pawn"));
	Mesh->SetupAttachment(RootComponent);

	MoveCmp = CreateDefaultSubobject<UBlobPawnMovementComponent>(TEXT("MoveCmp"));
	MoveCmp->UpdatedComponent = RootComponent;
}

void ABlobPiecePawn::SetupMove(float MoveSpeed, float iThickness)
{
	Thickness = iThickness;
	Mesh->SetRelativeScale3D(FVector(Thickness));

	FallDirectionY = FMath::FRandRange(0.f, 1.f) < 0.5f ? -1.f : 1.f;
	MoveDirection = FVector(0.f, MoveSpeed, StartSpeedZ);
}

void ABlobPiecePawn::DestroyBlobPiece()
{
	if (DestroyTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
	}
	Destroy();
}

// Called when the game starts or when spawned
void ABlobPiecePawn::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ABlobPiecePawn::DestroyBlobPiece, DeathDelay, false);
}

// Called every frame
void ABlobPiecePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	float DeltaY = FallDirectionY != 0.f ? FallDirectionY * (MoveDirection.Y * DeltaTime + A * DeltaTime * DeltaTime / 2.f) : 0.f;
	float DeltaZ = MoveDirection.Z * DeltaTime + G * DeltaTime * DeltaTime / 2.f;
	AddMovementInput(FVector(0.f, DeltaY, DeltaZ));

	MoveDirection.Y += A * DeltaTime;
	if (MoveDirection.Y < 0.f)
	{
		MoveDirection.Y = 0.f;
	}
	MoveDirection.Z += G * DeltaTime;

	Thickness -= Thickness * DeltaTime;
	Mesh->SetRelativeScale3D(FVector(Thickness));
}
