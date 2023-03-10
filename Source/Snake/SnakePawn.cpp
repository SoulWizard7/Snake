
#include "SnakePawn.h"
#include "Engine/World.h"
#include "DrawDebugHelpers.h"
#include "PaperSpriteComponent.h"
#include "SnakeNode.h"
#include "SnakeFood.h"
#include "SnakeGameMode.h"
#include "SnakePlayerController.h"

ASnakePawn::ASnakePawn(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	PrimaryActorTick.bCanEverTick = false;
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

void ASnakePawn::BeginPlay()
{
	Super::BeginPlay();

	GameMode = Cast<ASnakeGameMode>(GetWorld()->GetAuthGameMode());
	PlayerController = Cast<ASnakePlayerController>(GetController());
}

void ASnakePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	
	PlayerInputComponent->BindAction("MoveRight", EInputEvent::IE_Pressed, this, &ASnakePawn::MoveRight);
	PlayerInputComponent->BindAction("MoveLeft", EInputEvent::IE_Pressed, this, &ASnakePawn::MoveLeft);
	PlayerInputComponent->BindAction("MoveUp", EInputEvent::IE_Pressed, this, &ASnakePawn::MoveUp);
	PlayerInputComponent->BindAction("MoveDown", EInputEvent::IE_Pressed, this, &ASnakePawn::MoveDown);
}

//Main logic of movement

void ASnakePawn::SnakeTimerTick()
{
	FVector HeadPosition = SnakeHead->CurPos;	
	FVector NewHeadPosition = HeadPosition + CurDir * 64;

	SnakeHead->Move(NewHeadPosition);
/*
	SnakeHead->SetActorLocation(NewHeadPosition, false);

	if(SnakeHead->NextNode != nullptr)
	{		
		SnakeHead->NextNode->Move(HeadPosition);
	}
	
	SnakeHead->CurPos = NewHeadPosition;*/

	if(OutOfBounds(NewHeadPosition) || CrashIntoSelf(NewHeadPosition))
	{
		StopGame();
		return;
	}

	LastMoveDir = CurDir; //Makes sure we cannot turn into ourself/in a backwards direction
	FoodControl();
}

void ASnakePawn::SpawnSnakeHead()
{
	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SnakeHead = GetWorld()->SpawnActor<ASnakeNode>(SnakeNodeClass, FVector(0,0,0), FRotator::ZeroRotator,ActorSpawnParams);

	SnakeHead->SpriteComponent->SetSprite(PaperSprite);
	SnakeHead->CurPos = SnakeHead->GetActorLocation();
}

bool ASnakePawn::OutOfBounds(FVector Position)
{
	if(FMath::Abs(Position.X) > BoardSize * 64 - 10 || FMath::Abs(Position.Y) > BoardSize * 64 - 10)
	{
		return true;
	}
	return false;
}

bool ASnakePawn::CrashIntoSelf(FVector Position)
{
	ASnakeNode* Node = SnakeHead->NextNode;
	if(Node == nullptr) return false;

	while (Node->NextNode != nullptr)
	{
		if (Node->LastPos == Position)
		{
			return true;
		}
		Node = Node->NextNode;
	}
	return false;	
}

//The StartGame function works both as a Start and Restart function.
//I had originally split it into 2 functions but I had issues with the Widget scripts, where if I added too many buttons
//it would crash the engine. So I redid it into one functions since I did not understand the issue of the crash.

void ASnakePawn::StartGame()
{
	if(SnakeHead != nullptr)
	{
		SnakeHead->DestroySnake();
	}
	
	SpawnSnakeHead();
	if(SnakeHead)
	{		
		if(SnakeFood == nullptr)
		{
			SpawnFood();
		}
		else
		{
			MoveFood();
		}
	}		

	if(SnakeHead && SnakeFood && GameMode && PlayerController)
	{
		PlayerController->HideCursor();
		CurScore = 0;
		GameMode->SetScoreToWidget(CurScore);
		
		CurDir = FVector::ForwardVector;
		LastMoveDir = FVector::ForwardVector;
		
		if(bGameHasStarted)
		{			
			GetWorld()->GetTimerManager().UnPauseTimer(TimerHandle);
		}
		else
		{
			bGameHasStarted = true;
			GetWorld()->GetTimerManager().SetTimer(TimerHandle, this, &ASnakePawn::SnakeTimerTick, TickSpeed, true);
		}		
	}	
}

void ASnakePawn::SpawnFood()
{
	FVector SpawnLocation = FVector::ZeroVector;
	while (SpawnLocation == FVector::ZeroVector)
	{
		SpawnLocation = FVector(FMath::RandRange(-(BoardSize - 1), (BoardSize - 1)) * 64, FMath::RandRange(-(BoardSize - 1), (BoardSize - 1)) * 64, 0);		
	}	

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	SnakeFood = GetWorld()->SpawnActor<ASnakeFood>(SnakeFoodClass, SpawnLocation, FRotator::ZeroRotator, ActorSpawnParams);
}

void ASnakePawn::FoodControl()
{
	if(SnakeFood->GetActorLocation() == SnakeHead->GetActorLocation())
	{
		AddNode();
		MoveFood();		
		CurScore++;
		GameMode->SetScoreToWidget(CurScore);
	}
}

void ASnakePawn::StopGame()
{
	GetWorld()->GetTimerManager().PauseTimer(TimerHandle);
	PlayerController->ShowCursor();
}

void ASnakePawn::AddNode()
{
	ASnakeNode* Node = SnakeHead;
	while(Node->NextNode != nullptr)
	{
		Node = Node->NextNode;
	}

	FActorSpawnParameters ActorSpawnParams;
	ActorSpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	Node->NextNode = GetWorld()->SpawnActor<ASnakeNode>(SnakeNodeClass, Node->CurPos, FRotator::ZeroRotator,ActorSpawnParams);	
}


//MoveFood checks if any of the snake nodes are on the new location before moving to an unoccupied space.

void ASnakePawn::MoveFood()
{
	FVector NewPos = FVector(FMath::RandRange(-(BoardSize - 1), (BoardSize - 1)) * 64, FMath::RandRange(-(BoardSize - 1), (BoardSize - 1)) * 64, 0);
	ASnakeNode* Node = SnakeHead;
	while (Node != nullptr)
	{
		if (Node->CurPos == NewPos)
		{
			NewPos = FVector(FMath::RandRange(-(BoardSize - 1), (BoardSize - 1)) * 64, FMath::RandRange(-(BoardSize - 1), (BoardSize - 1)) * 64, 0);
			Node = SnakeHead;
		}
		Node = Node->NextNode;
	}
	SnakeFood->SetActorLocation(NewPos);
}

void ASnakePawn::MoveRight()
{
	if(LastMoveDir != FVector::LeftVector)
	{
		CurDir = FVector::RightVector;
	}	
}

void ASnakePawn::MoveLeft()
{
	if(LastMoveDir != FVector::RightVector)
	{
		CurDir = FVector::LeftVector;
	}	
}

void ASnakePawn::MoveUp()
{
	if(LastMoveDir != FVector::BackwardVector)
	{
		CurDir = FVector::ForwardVector;
	}	
}

void ASnakePawn::MoveDown()
{	
	if(LastMoveDir != FVector::ForwardVector)
	{
		CurDir = FVector::BackwardVector;
	}	
}