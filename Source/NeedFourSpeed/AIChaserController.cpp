// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "AIChaserController.h"
#include "Engine.h"
#include "AICharacter.h"

AAIChaserController::AAIChaserController()
{
	mAnimState = Start;
	mAttackRange = 30.0f;
}

void AAIChaserController::BeginPlay()
{
	Super::BeginPlay();
}

void AAIChaserController::Tick(float deltaTime)
{
	Super::Tick(deltaTime);

	//Need to get the closest target that is within range
	APawn* player = GetClosestPlayer();
	if (player&&GetPawn())
	{
		//Look at the player
		FRotator AIRot = (player->GetActorLocation() - GetPawn()->GetActorLocation()).Rotation();
		GetPawn()->SetActorRotation(AIRot);
		float distToPlayer = FVector::Dist(GetPawn()->GetActorLocation(), player->GetActorLocation());
		if (mAnimState == Start)
		{
			if (distToPlayer <= mVisionRange)
			{
				ChasePlayer(player);
			}
		}
		else
		{
			//Check to see if the player is still in range
			if (player) {
				if (distToPlayer > mAttackRange)
				{
					ChasePlayer(player);

					//Stop the attack animation
					AAICharacter* player = Cast<AAICharacter>(GetPawn());
					player->StopAttack();
				}
			}
		}
	}
}

void AAIChaserController::OnMoveCompleted(FAIRequestID iD, EPathFollowingResult::Type result)
{
	if (result == EPathFollowingResult::Success)
	{
		mAnimState = Attack;
	}
}


