// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeNode.generated.h"

class UPaperSpriteComponent;
class AActor;

//This snake node is just a very basic linked-list

UCLASS()
class SNAKE_API ASnakeNode : public AActor
{
	GENERATED_BODY()

public:
	
	ASnakeNode();

	UPROPERTY(Category = Block, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* DummyRoot;
	
	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* SpriteComponent;	

	UPROPERTY()
	ASnakeNode* NextNode;

	UPROPERTY()
	FVector CurPos;

	UPROPERTY()
	FVector LastPos;

	UFUNCTION()
	void Move(FVector NewPos);

	UFUNCTION()
	void DestroySnake();
};
