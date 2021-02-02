// Fill out your copyright notice in the Description page of Project Settings.


#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"

#include "BlobPawnMovementComponent.h"
#include "BlobPawn.h"

const FName ABlobPawn::MoveForwardBinding("MoveForward");
const FName ABlobPawn::MoveRightBinding("MoveRight");

// Sets default values
ABlobPawn::ABlobPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Wrapper = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Wrapper;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetCollisionProfileName(TEXT("Pawn"));
	Mesh->SetupAttachment(RootComponent);

	CapsuleCmp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleCmp->SetRelativeScale3D(FVector(5.f, 3.f, 1.25f));
	CapsuleCmp->SetCollisionProfileName(TEXT("Pawn"));
	CapsuleCmp->SetupAttachment(Mesh);

	CameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	CameraArm->TargetArmLength = 900.f;
	CameraArm->bUsePawnControlRotation = false;
	CameraArm->SetupAttachment(RootComponent);

	CameraCmp = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraCmp"));
	CameraCmp->bUsePawnControlRotation = false;
	CameraCmp->SetupAttachment(CameraArm, USpringArmComponent::SocketName);

	MoveCmp = CreateDefaultSubobject<UBlobPawnMovementComponent>(TEXT("MoveCmp"));
	MoveCmp->UpdatedComponent = RootComponent;
}

// Called when the game starts or when spawned
void ABlobPawn::BeginPlay()
{
	Super::BeginPlay();

	MoveSpeed = MinMoveSpeed;
	Thickness = MaxThickness / 2.f;

	// Statictics
	TimeTravelled = 0.f;
	DistanceTravelled = 0.f;
	MaxAccumulatedThickness = Thickness;
	MaxAccumulatedSpeed = MoveSpeed;
	ObstaclesHitCount = 0;
	DropletsCollectedCount = 0;
}

// Called every frame
void ABlobPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	// Clamp max size so that (X=1, Y=1) doesn't cause faster movement in diagonal directions
	const FVector MoveDirection = FVector(0.f, RightValue, ForwardValue).GetClampedToMaxSize(1.0f);

	float AccelerationZ = G * DeltaTime;
	// Adjust vertical speed based on input
	if (MoveDirection.Z != 0)
	{
		MoveSpeed = MoveDirection.Z < 0 ? FGenericPlatformMath::Min(MoveSpeed + 2 * AccelerationZ, MaxMoveSpeed) : FGenericPlatformMath::Max(MoveSpeed - 2 * AccelerationZ, MinMoveSpeed);
	}
	// Adjust vertical speed based on gravity
	MoveSpeed = FGenericPlatformMath::Min(MoveSpeed + AccelerationZ, MaxMoveSpeed);

	// Calculate  movement
	const FVector Movement = FVector(MoveDirection.X, MoveDirection.Y * MoveSpeedH, -MoveSpeed);
	AddMovementInput(Movement, DeltaTime);

	float DeltaDistance = Movement.Size();
	float ThicknessReduction = ThicknessDropRate * DeltaDistance * DeltaTime;

	/*if (DeltaDistance > 0.f)
	{
		FHitResult Hit(1.f);
		RootComponent->MoveComponent(Movement, RootComponent->GetComponentRotation(), true, &Hit);

		if (Hit.IsValidBlockingHit())
		{
			GEngine->AddOnScreenDebugMessage(0, 5.f, FColor::White, FString("Hit catched"));
			MoveSpeed = MinMoveSpeed;
			ObstaclesHitCount++;
			ThicknessReduction = ThicknessDropRate * 10.f;

			const FVector Normal2D = Hit.Normal.GetSafeNormal2D();
			const FVector Deflection = FVector::VectorPlaneProject(Movement, Normal2D) * (1.f - Hit.Time);
			RootComponent->MoveComponent(Deflection, RootComponent->GetComponentRotation(), true);
		}
	}*/

	// Reduce blob thickness based on distance travelled
	Thickness = FGenericPlatformMath::Max(Thickness - ThicknessReduction, MinThickness);
	RootComponent->GetChildComponent(0)->SetRelativeScale3D(FVector(Thickness));

	// Update statistics
	TimeTravelled += DeltaTime;
	DistanceTravelled += DeltaDistance;
	MaxAccumulatedThickness = FGenericPlatformMath::Max(Thickness, MaxAccumulatedThickness);
	MaxAccumulatedSpeed = FGenericPlatformMath::Max(MoveSpeed, MaxAccumulatedSpeed);
}

// Called to bind functionality to input
void ABlobPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis(MoveForwardBinding);
	PlayerInputComponent->BindAxis(MoveRightBinding);
}

UPawnMovementComponent* ABlobPawn::GetMovementComponent() const
{
	return MoveCmp;
}
