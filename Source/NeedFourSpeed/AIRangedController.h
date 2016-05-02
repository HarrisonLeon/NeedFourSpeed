// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AICharacterController.h"
#include "AIRangedController.generated.h"

/**
 * 
 */
UCLASS()
class NEEDFOURSPEED_API AAIRangedController : public AAICharacterController
{
	GENERATED_BODY()

	AAIRangedController();

	void BeginPlay();

	void Tick(float deltaTime);

	void OnMoveCompleted(FAIRequestID iD, EPathFollowingResult::Type result) override;

	APawn* FindClosestPlayer();

private:
	
	
	
};
