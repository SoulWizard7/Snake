// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SnakeUIWidget.generated.h"

class UTextBlock;
class UButton;

UCLASS()
class SNAKE_API USnakeUIWidget : public UUserWidget
{
	GENERATED_BODY()

	virtual bool Initialize();	
	
public:

	UFUNCTION()
	void StartGame();

	UFUNCTION()
	void QuitGame();	
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ScoreTextBlock;

	UPROPERTY(meta = (BindWidget))
	UButton* StartGameButton;

	UPROPERTY(meta = (BindWidget))
	UButton* QuitButton;
};
