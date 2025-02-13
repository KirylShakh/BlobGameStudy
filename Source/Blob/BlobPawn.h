// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "BlobPawn.generated.h"

class ABlobPiecePawn;

UCLASS()
class BLOB_API ABlobPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ABlobPawn();

	// Static names for axis bindings
	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* CapsuleCmp;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class USpringArmComponent* CameraArm;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UCameraComponent* CameraCmp;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UBlobPawnMovementComponent* MoveCmp;

	class UBlobGameInstance* BlobGameInstance;

	UFUNCTION(BlueprintImplementableEvent, Category="BlobPawn")
	void OnDriedOut();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// To store base proportions of the pawn
	FVector BaseScale;

public:
	// The min speed blob can fall
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MinMoveSpeed = 1;

	// The max speed blob can fall
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MaxMoveSpeed = 100;

	// The gravity acceleration
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float G = 10;

	// Game is over when blob thickness falls to that value
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MinThickness = .1f;

	// How much water can be accumulated in droplet
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float MaxThickness = 2.f;

	// Starting factor value of how much water can be accumulated in droplet
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float StartingThickness = 1.f;

	// How fast thickness will fall during movement
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float ThicknessDropRate = .001f;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadWrite)
	float LostOnHitPart = .1f;

	UPROPERTY(EditAnywhere, Category = Gameplay)
	TSubclassOf<ABlobPiecePawn> BlopPieceClass;

	// Factor of scale - shows how much water is currently present in droplet
	float Thickness;

	// Current fall speed
	float MoveSpeed;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UPawnMovementComponent* GetMovementComponent() const override;

	void UpdateThickness(float DeltaThickness);

	void SpawnBlobPiece();
};
