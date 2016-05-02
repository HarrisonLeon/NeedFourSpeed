// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AIController.h"
#include "AICharacterController.generated.h"

enum AnimState {
	Start,
	Chase,
	Attack,
	Dead
};

/**
 * 
 */
UCLASS()
class NEEDFOURSPEED_API AAICharacterController : public AAIController
{
	GENERATED_BODY()
public:
	AAICharacterController();
	virtual void BeginPlay();
	virtual void Tick(float deltaTime);
	virtual void OnMoveCompleted(FAIRequestID iD, EPathFollowingResult::Type result);
	APawn* GetClosestPlayer();

protected:
	void ChasePlayer(APawn* player);

	AnimState mAnimState;
	
	UPROPERTY(EditAnywhere)
		float mAttackRange = 1000.0f;

	UPROPERTY(EditAnywhere)
		float mVisionRange = 1600.0f;
	
};
