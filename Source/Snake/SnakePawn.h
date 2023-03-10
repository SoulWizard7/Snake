// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "SnakePawn.generated.h"

class APawn;
class ASnakeFood;
class ASnakeNode;
class UPaperSprite;
class UTexture;
class ASnakeGameMode;
class ASnakePlayerController;

//The SnakePawn includes most of the logic behind the game.
//It uses a TimerManager timer that is on a loop instead of a tick to move the snake.

UCLASS(config=Game)
class ASnakePawn : public APawn
{
	GENERATED_UCLASS_BODY()

public:

	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	UFUNCTION()
	void StartGame();

private:

	//// References ////
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeNode> SnakeNodeClass;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<ASnakeFood> SnakeFoodClass;

	UPROPERTY(EditDefaultsOnly)
	UPaperSprite* PaperSprite;

	UPROPERTY()
	ASnakeFood* SnakeFood;
	
	UPROPERTY()
	ASnakeNode* SnakeHead;

	UPROPERTY()
	ASnakeGameMode* GameMode;

	UPROPERTY()
	ASnakePlayerController* PlayerController;	

	//// Variables ////

	UPROPERTY()
	FVector CurPos = FVector(0,0,0);
	
	UPROPERTY()
	FVector CurDir = FVector(1,0,0);

	UPROPERTY()
	FVector LastMoveDir = FVector(1,0,0);

	UPROPERTY()
	FTimerHandle TimerHandle;

	UPROPERTY()
	int BoardSize = 10;

	UPROPERTY()
	float TickSpeed = 0.25f;

	UPROPERTY()
	int CurScore = 0;

	UPROPERTY()
	bool bGameHasStarted = false;	
	
	//// Functions ////
	
	UFUNCTION()
	void SnakeTimerTick();

	UFUNCTION()
	void SpawnSnakeHead();
	
	UFUNCTION()
	void AddNode();

	UFUNCTION()
	bool OutOfBounds(FVector Position);

	UFUNCTION()
	bool CrashIntoSelf(FVector Position);	

	UFUNCTION()
	void SpawnFood();

	UFUNCTION()
	void MoveFood();

	UFUNCTION()
	void FoodControl();

	UFUNCTION()
	void StopGame();
	
	void MoveRight();
	void MoveLeft();
	void MoveUp();
	void MoveDown();
	
};





