// Fill out your copyright notice in the Description page of Project Settings.


#include "BlobPawn.h"
#include "BlobGameInstance.h"
#include "BlobPawnMovementComponent.h"
#include "BlobPiecePawn.h"

#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Kismet/GameplayStatics.h"

const FName ABlobPawn::MoveForwardBinding("MoveForward");
const FName ABlobPawn::MoveRightBinding("MoveRight");

// Sets default values
ABlobPawn::ABlobPawn()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CapsuleCmp = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule"));
	CapsuleCmp->SetRelativeScale3D(FVector(1.5f, 1.5f, .8f));
	CapsuleCmp->SetCollisionProfileName(TEXT("Pawn"));
	SetRootComponent(CapsuleCmp);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	Mesh->SetCollisionProfileName(TEXT("Pawn"));
	Mesh->SetRelativeScale3D(FVector(.45f, .45f, .8f));
	Mesh->SetupAttachment(CapsuleCmp);

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

	BaseScale = RootComponent->GetRelativeScale3D();
	Thickness = StartingThickness;
	MoveSpeed = MinMoveSpeed;

	BlobGameInstance = Cast<UBlobGameInstance>(UGameplayStatics::GetGameInstance(this));
	BlobGameInstance->ResetStatistics();
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

	// Calculate horizontal offset
	float MoveH = MoveDirection.Y * MoveSpeed;

	// Calculate  movement
	const FVector Movement = FVector(MoveDirection.X, MoveH, -MoveSpeed);
	AddMovementInput(Movement, DeltaTime);

	float DeltaDistance = Movement.Size();
	float ThicknessReduction = ThicknessDropRate * DeltaDistance * DeltaTime;
	// Reduce blob thickness based on distance travelled
	UpdateThickness(-ThicknessReduction);

	// Update statistics
	BlobGameInstance->TimeTravelled += DeltaTime;
	BlobGameInstance->DistanceTravelled += DeltaDistance;
	BlobGameInstance->MaxAccumulatedThickness = FGenericPlatformMath::Max(Thickness, BlobGameInstance->MaxAccumulatedThickness);
	BlobGameInstance->MaxAccumulatedSpeed = FGenericPlatformMath::Max(MoveSpeed, BlobGameInstance->MaxAccumulatedSpeed);
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

void ABlobPawn::UpdateThickness(float DeltaThickness)
{
	Thickness = FMath::Clamp(Thickness + DeltaThickness, MinThickness, MaxThickness);
	if (Thickness == MinThickness)
	{
		SetActorTickEnabled(false);
		OnDriedOut();
	}

	RootComponent->SetRelativeScale3D(BaseScale * Thickness);
}

void ABlobPawn::SpawnBlobPiece()
{
	float LostThickness = Thickness * LostOnHitPart;
	UpdateThickness(-LostThickness);

	float LostSpeed = MoveSpeed * LostOnHitPart;
	MoveSpeed = FGenericPlatformMath::Max(MoveSpeed - LostSpeed, MinMoveSpeed);

	// Spawn blob piece
	FActorSpawnParameters SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	ABlobPiecePawn* BlobPiece = GetWorld()->SpawnActor<ABlobPiecePawn>(BlopPieceClass, FTransform(GetTransform().GetLocation()), SpawnParameters);
	if (BlobPiece)
	{
		BlobPiece->SetupMove(LostSpeed * 2, LostThickness);
	}
}
