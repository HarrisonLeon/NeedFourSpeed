// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AICharacterController.h"
#include "AIChaserController.generated.h"

/**
 * 
 */
UCLASS()
class NEEDFOURSPEED_API AAIChaserController : public AAICharacterController
{
	GENERATED_BODY()

	AAIChaserController();

	void BeginPlay();

	void Tick(float deltaTime);

	void OnMoveCompleted(FAIRequestID iD, EPathFollowingResult::Type result) override;

	APawn* FindClosestPlayer();

private:

	
};
