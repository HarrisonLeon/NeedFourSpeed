// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "SpawnManager.h"
#include "ShipCharacter.h"
#include "GoalNode.generated.h"


/**
 * 
 */
UCLASS()
class NEEDFOURSPEED_API AGoalNode : public APickUp
{
	GENERATED_BODY()
public:
	AGoalNode();
	void SetSpawnManager(ASpawnManager* sm);
	void PickUp(AShipCharacter* player) override;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		class USoundCue* mCollectSound;

private:
	ASpawnManager* sm;
	UAudioComponent* PlayCollectSound(USoundCue* sound);
	
	
	
};
