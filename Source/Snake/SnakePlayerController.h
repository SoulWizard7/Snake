// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "SnakePlayerController.generated.h"

/** PlayerController class used to enable cursor */
UCLASS()
class ASnakePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	ASnakePlayerController();

	UFUNCTION()
	void HideCursor();

	UFUNCTION()
	void ShowCursor();

	UFUNCTION()
	void StartGame();
};


