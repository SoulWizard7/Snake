// Fill out your copyright notice in the Description page of Project Settings.


#include "SnakeFood.h"
#include "PaperSpriteComponent.h"


ASnakeFood::ASnakeFood()
{
	PrimaryActorTick.bCanEverTick = false;
	
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = DummyRoot;
	
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComponent->SetupAttachment(DummyRoot);
	SpriteComponent->SetWorldRotation(FRotator(0, 90, -90));	
}


