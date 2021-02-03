// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Droplet.generated.h"

UCLASS()
class BLOB_API ADroplet : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADroplet();

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class USceneComponent* Wrapper;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UStaticMeshComponent* Mesh;

	UPROPERTY(Category = "Components", EditAnywhere, BlueprintReadWrite)
	class UCapsuleComponent* CapsuleCmp;

	UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite)
	float MinThickness = .3f;

	UPROPERTY(Category = "Config", EditAnywhere, BlueprintReadWrite)
	float MaxThickness = 1.f;

	UFUNCTION(BlueprintNativeEvent, Category = Collision)
	void OnTrigger(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	void OnTrigger_Implementation(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	float Thickness;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
