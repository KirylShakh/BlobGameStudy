// Fill out your copyright notice in the Description page of Project Settings.


#include "Kismet/GameplayStatics.h"
#include "Engine/Canvas.h"
#include "BlobCharacter.h"
#include "BlobHUD.h"

void ABlobHUD::DrawHUD()
{
    Super::DrawHUD();

    int32 CanvasX = Canvas->SizeX;
    int32 CanvasY = Canvas->SizeY;

    ABlobCharacter* Blob = Cast<ABlobCharacter>(UGameplayStatics::GetPlayerPawn(GetWorld(), 0));
    TArray<FString> Messages;
    Messages.Add("Time travelled: " + FString::SanitizeFloat(Blob->TimeTravelled));
    Messages.Add("Distance travelled: " + FString::SanitizeFloat(Blob->DistanceTravelled));
    Messages.Add("Maximum accumulated thickness: " + FString::SanitizeFloat(Blob->MaxAccumulatedThickness));
    Messages.Add("Maximum accumulated speed: " + FString::SanitizeFloat(Blob->MaxAccumulatedSpeed));
    Messages.Add("Obstacles hit count: " + FString::FromInt(Blob->ObstaclesHitCount));
    Messages.Add("Droplets collected count: " + FString::FromInt(Blob->DropletsCollectedCount));

    Messages.Add("Current thickness: " + FString::SanitizeFloat(Blob->Thickness));
    Messages.Add("Current fall speed: " + FString::SanitizeFloat(Blob->MoveSpeed));

    Messages.Add("Canvas X: " + FString::FromInt(CanvasX));
    Messages.Add("Canvas Y: " + FString::FromInt(CanvasY));

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

