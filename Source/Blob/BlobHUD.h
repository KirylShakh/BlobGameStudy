// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "BlobHUD.generated.h"

class ABlobPawn;

UCLASS()
class BLOB_API ABlobHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = HUDFont)
	UFont* HudFont;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text)
	float PadX = 50.f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Text)
	float PadY = 20.f;

	virtual void DrawHUD() override;

protected:
	void DrawEndgameStats(ABlobPawn* Blob, int32 CanvasX, int32 CanvasY);

	void DrawIngameStats(ABlobPawn* Blob);

	TArray<FString> GetStats(ABlobPawn* Blob);
};
