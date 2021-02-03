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

	float Thickness;
	FVector MoveDirection;
	float G = -50.f;
	float A = -10.f;
	float FallDirectionY;

	void SetupMove(float MoveSpeed, float iThickness);

	UPROPERTY()
	FTimerHandle DestroyTimerHandle;
	float DeathDelay = 2.f;
	void DestroyBlobPiece();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
