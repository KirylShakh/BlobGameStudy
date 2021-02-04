// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "BlobPiecePawn.generated.h"

UCLASS()
class BLOB_API ABlobPiecePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ABlobPiecePawn();

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Wrapper;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UBlobPawnMovementComponent* MoveCmp;

	// Vertical acceleration
	UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite)
	float G = -50.f;

	// Horizontal acceleration
	UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite)
	float A = -10.f;

	void SetupMove(float MoveSpeed, float iThickness);

	// Death properties
	UPROPERTY()
	FTimerHandle DestroyTimerHandle;

	float DeathDelay = 2.f;
	void DestroyBlobPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// How much water is there in a blob piece (scale)
	float Thickness;

	// Vector to store current move speeds
	FVector MoveDirection;

	// Starting vertical speed (currently pieces will fly upwards for a short time)
	float StartSpeedZ = 50.f;

	// Random horizontal direction of the piece - will it fly left or right from the blob
	float FallDirectionY;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
