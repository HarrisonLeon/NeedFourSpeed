// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "AICharacter.h"
#include "Engine.h"
#include "NeedFourSpeedGameMode.h"
#include "AICharacterController.h"

AAICharacterController::AAICharacterController()
{
	mAnimState = Start;
}

void AAICharacterController::BeginPlay()
{
	Super::BeginPlay();
	//APawn* player = UGameplayStatics::GetPlayerPawn(this, 1);
	//MoveToActor(player);
}

void AAICharacterController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);
}


APawn* AAICharacterController::GetClosestPlayer()
{
	TArray<APlayerController*> playerControllers = Cast<ANeedFourSpeedGameMode>(GetWorld()->GetAuthGameMode())->getAllPlayerControllers();
	APawn* closestPlayer=nullptr;
	for (int i = 0; i < playerControllers.Num(); i++)
	{
		APawn* currPlayer = playerControllers[i]->GetPawn();
		if (currPlayer)
		{
			if (!closestPlayer)
			{
				closestPlayer = currPlayer;
			}
			else if(closestPlayer)
			{
				if (this->GetPawn()&&(this->GetPawn()->GetActorLocation() - currPlayer->GetActorLocation()).SizeSquared() <
					(this->GetPawn()->GetActorLocation() - closestPlayer->GetActorLocation()).SizeSquared())

				{
					closestPlayer = currPlayer;
				}
			}
		}
	}
	return closestPlayer;
}

void AAICharacterController::ChasePlayer(APawn* player)
{
	MoveToActor(player,mAttackRange,true,true,true,NULL,true);
	mAnimState = Chase;
}

void AAICharacterController::OnMoveCompleted(FAIRequestID iD, EPathFollowingResult::Type result)
{
	if (result == EPathFollowingResult::Success)
	{
		mAnimState = Attack;

		//Start the attack animation
		AAICharacter* player = Cast<AAICharacter>(GetPawn());
		player->StartAttack();
	}
}


