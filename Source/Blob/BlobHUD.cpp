// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "BlobPawn.h"
#include "BlobHUD.h"

void ABlobHUD::DrawHUD()
{
    Super::DrawHUD();

    ABlobPawn* Blob = Cast<ABlobPawn>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    if (!Blob)
    {
        return;
    }

    //DrawEndgameStats(Blob, Canvas->SizeX, Canvas->SizeY);
}

void ABlobHUD::DrawEndgameStats(ABlobPawn* Blob, int32 CanvasX, int32 CanvasY)
{
    //DrawRect(FLinearColor::Black, 0.f, 0.f, CanvasX, CanvasY);
    //DrawIngameStats(Blob);
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
    /*Messages.Add("Time travelled: " + FString::SanitizeFloat(Blob->TimeTravelled));
    Messages.Add("Distance travelled: " + FString::SanitizeFloat(Blob->DistanceTravelled));
    Messages.Add("Maximum accumulated thickness: " + FString::SanitizeFloat(Blob->MaxAccumulatedThickness));
    Messages.Add("Maximum accumulated speed: " + FString::SanitizeFloat(Blob->MaxAccumulatedSpeed));
    Messages.Add("Obstacles hit count: " + FString::FromInt(Blob->ObstaclesHitCount));
    Messages.Add("Droplets collected count: " + FString::FromInt(Blob->DropletsCollectedCount));

    Messages.Add("Current thickness: " + FString::SanitizeFloat(Blob->Thickness));
    Messages.Add("Current fall speed: " + FString::SanitizeFloat(Blob->MoveSpeed));*/

    return Messages;
}

