// Copyright Epic Games, Inc. All Rights Reserved.

#include "SnakeGameMode.h"
#include "SnakePlayerController.h"
#include "SnakePawn.h"
#include "Blueprint/UserWidget.h"
#include "Components/TextBlock.h"
#include "Widgets/SnakeUIWidget.h"

ASnakeGameMode::ASnakeGameMode()
{
	// no pawn by default
	DefaultPawnClass = ASnakePawn::StaticClass();
	// use our own player controller class
	PlayerControllerClass = ASnakePlayerController::StaticClass();
}

void ASnakeGameMode::BeginPlay()
{
	Super::BeginPlay();
	
	if(IsValid(WidgetClass))
	{
		TextWidget = Cast<USnakeUIWidget>(CreateWidget(GetWorld(), WidgetClass));

		if(TextWidget != nullptr)
		{
			TextWidget->AddToViewport();
			SetScoreToWidget(0);
		}
	}
}

void ASnakeGameMode::SetScoreToWidget(int score)
{
	if(TextWidget != nullptr)
	{		
		TextWidget->ScoreTextBlock->SetText(FText::FromString(FString::Printf(TEXT("Score: %i"), score)));		
	}
}
