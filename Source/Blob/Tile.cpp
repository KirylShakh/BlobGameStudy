// Fill out your copyright notice in the Description page of Project Settings.


#include "Tile.h"
#include "BlobGameMode.h"
#include "BlobPawn.h"

#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
ATile::ATile()
{
 	Wrapper = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Wrapper;

	TriggerBox = CreateDefaultSubobject<UBoxComponent>(TEXT("TriggerBox"));
	TriggerBox->SetupAttachment(RootComponent);
	TriggerBox->SetBoxExtent(FVector(128.f, 1000.f, 200.f));
	TriggerBox->SetCollisionProfileName(TEXT("OverlapOnlyPawn"));
}

void ATile::AddPlaceble(AActor* Placeble)
{
	Placebles.Add(Placeble);
	Placeble->OnDestroyed.AddDynamic(this, &ATile::OnPlacebleDestroyed);
}

// Called when the game starts or when spawned
void ATile::BeginPlay()
{
	Super::BeginPlay();
	
	BlobGameMode = Cast<ABlobGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	check(BlobGameMode);

	TriggerBox->OnComponentBeginOverlap.AddDynamic(this, &ATile::OnTrigger);
}

void ATile::OnTrigger_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (Cast<ABlobPawn>(OtherActor))
	{
		BlobGameMode->AddTile();
		GetWorldTimerManager().SetTimer(DestroyTimerHandle, this, &ATile::DestroyTile, DeathDelay, false);
	}
}

void ATile::DestroyTile()
{
	if (DestroyTimerHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(DestroyTimerHandle);
	}

	for (int i = 0; i < Placebles.Num(); i++)
	{
		if (Placebles[i])
		{
			Placebles[i]->Destroy();
		}
	}
	Placebles.Empty();

	Destroy();
}

void ATile::OnPlacebleDestroyed(AActor* DestroyedActor)
{
	if (Placebles.Find(DestroyedActor) != -1)
	{
		Placebles.Remove(DestroyedActor);
	}
}
