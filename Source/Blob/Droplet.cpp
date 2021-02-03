// Fill out your copyright notice in the Description page of Project Settings.

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"

#include "BlobGameInstance.h"
#include "BlobPawn.h"
#include "Droplet.h"

// Sets default values
ADroplet::ADroplet()
{
	Wrapper = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Wrapper;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetupAttachment(RootComponent);

	CapsuleCmp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleCmp->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
	CapsuleCmp->SetRelativeScale3D(FVector(2.5f, 2.5f, 1.25f));
	CapsuleCmp->SetupAttachment(Mesh);
}

// Called when the game starts or when spawned
void ADroplet::BeginPlay()
{
	Super::BeginPlay();

	Thickness = FMath::FRandRange(MinThickness, MaxThickness);
	Mesh->SetRelativeScale3D(FVector(Thickness));
	
	CapsuleCmp->OnComponentBeginOverlap.AddDynamic(this, &ADroplet::OnTrigger);
}

void ADroplet::OnTrigger_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	ABlobPawn* Blob = Cast<ABlobPawn>(OtherActor);
	if (Blob)
	{
		Blob->BlobGameInstance->DropletsCollectedCount++;
		Blob->UpdateThickness(Thickness);
		Destroy();
	}
}
