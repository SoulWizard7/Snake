
#include "SnakeNode.h"
#include "PaperSpriteComponent.h"


ASnakeNode::ASnakeNode()
{
	PrimaryActorTick.bCanEverTick = false;
	DummyRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = DummyRoot;
	SpriteComponent = CreateDefaultSubobject<UPaperSpriteComponent>(TEXT("Sprite"));
	SpriteComponent->SetupAttachment(DummyRoot);	
}

void ASnakeNode::Move(FVector NewPos)
{
	LastPos = CurPos;
	CurPos = NewPos;
	SetActorLocation(CurPos, false);	
	
	if (NextNode != nullptr)
	{
		NextNode->Move(LastPos);
	}	
}

void ASnakeNode::DestroySnake()
{
	if(NextNode != nullptr)
	{
		NextNode->DestroySnake();
	}
	K2_DestroyActor();
}

