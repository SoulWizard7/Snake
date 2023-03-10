// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SnakeFood.generated.h"

class UPaperSpriteComponent;
class AActor;

UCLASS()
class SNAKE_API ASnakeFood : public AActor
{
	GENERATED_BODY()

public:
	
	ASnakeFood();

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
	USceneComponent* DummyRoot;
	
	UPROPERTY(EditAnywhere)
	UPaperSpriteComponent* SpriteComponent;
	
};
