// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeUIWidget.h"

#include "Components/Button.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Snake/SnakePlayerController.h"


bool USnakeUIWidget::Initialize()
{
	Super::Initialize();	

	StartGameButton->OnClicked.AddDynamic(this, &USnakeUIWidget::StartGame);
	QuitButton->OnClicked.AddDynamic(this, &USnakeUIWidget::QuitGame);	
	return true;
}

void USnakeUIWidget::StartGame()
{
	ASnakePlayerController* PlayerController = Cast<ASnakePlayerController>(GetWorld()->GetFirstPlayerController());
	if(PlayerController)
	{
		PlayerController->StartGame();	
	}
}

void USnakeUIWidget::QuitGame()
{	
	UKismetSystemLibrary::QuitGame(GetWorld(), GetWorld()->GetFirstPlayerController(), EQuitPreference::Quit, true);
}