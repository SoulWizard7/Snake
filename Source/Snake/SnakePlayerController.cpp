// Copyright Epic Games, Inc. All Rights Reserved.

#include "SnakePlayerController.h"

#include "SnakePawn.h"

ASnakePlayerController::ASnakePlayerController()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableTouchEvents = true;
	DefaultMouseCursor = EMouseCursor::Crosshairs;
}

void ASnakePlayerController::HideCursor()
{
	bShowMouseCursor = false;
}

void ASnakePlayerController::ShowCursor()
{
	bShowMouseCursor = true;
}

void ASnakePlayerController::StartGame()
{
	Cast<ASnakePawn>(GetPawn())->StartGame();
}
