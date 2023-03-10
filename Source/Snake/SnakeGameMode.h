// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SnakeGameMode.generated.h"

class USnakeUIWidget;

UCLASS(minimalapi)
class ASnakeGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ASnakeGameMode();	

	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UUserWidget> WidgetClass;

	UPROPERTY(VisibleInstanceOnly)
	USnakeUIWidget* TextWidget;

	UFUNCTION()
	void SetScoreToWidget(int score);
	
};



