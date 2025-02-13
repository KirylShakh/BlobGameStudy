// Fill out your copyright notice in the Description page of Project Settings.


#include "BlobHUD.h"
#include "BlobGameInstance.h"
#include "BlobPawn.h"

#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"

void ABlobHUD::DrawHUD()
{
    Super::DrawHUD();

    ABlobPawn* Blob = Cast<ABlobPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (!Blob)
    {
        return;
    }
}

void ABlobHUD::DrawEndgameStats(ABlobPawn* Blob, int32 CanvasX, int32 CanvasY)
{
    DrawRect(FLinearColor::Black, 0.f, 0.f, CanvasX, CanvasY);
    DrawIngameStats(Blob);
}

void ABlobHUD::DrawIngameStats(ABlobPawn* Blob)
{
    TArray<FString> Messages = GetStats(Blob);
    for (int i = Messages.Num() - 1; i >= 0; i--)
    {
        float outputWidth, outputHeight;
        GetTextSize(Messages[i], outputWidth, outputHeight, HudFont, 1.f);
        float messageH = outputHeight + 2.f * PadY;
        float x = 0.f, y = i * messageH;

        DrawText(Messages[i], FLinearColor::White, x + PadX, y + PadY, HudFont, 1.0f);
    }

    Messages.Empty();
}

TArray<FString> ABlobHUD::GetStats(ABlobPawn* Blob)
{
    TArray<FString> Messages;
    Messages.Add("Time travelled: " + FString::SanitizeFloat(Blob->BlobGameInstance->TimeTravelled));
    Messages.Add("Distance travelled: " + FString::SanitizeFloat(Blob->BlobGameInstance->DistanceTravelled));
    Messages.Add("Maximum accumulated thickness: " + FString::SanitizeFloat(Blob->BlobGameInstance->MaxAccumulatedThickness));
    Messages.Add("Maximum accumulated speed: " + FString::SanitizeFloat(Blob->BlobGameInstance->MaxAccumulatedSpeed));
    Messages.Add("Obstacles hit count: " + FString::FromInt(Blob->BlobGameInstance->ObstaclesHitCount));
    Messages.Add("Droplets collected count: " + FString::FromInt(Blob->BlobGameInstance->DropletsCollectedCount));

    Messages.Add("Current thickness: " + FString::SanitizeFloat(Blob->Thickness));
    Messages.Add("Current fall speed: " + FString::SanitizeFloat(Blob->MoveSpeed));

    return Messages;
}

