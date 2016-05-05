// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerState.h"
#include "ShipPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class NEEDFOURSPEED_API AShipPlayerState : public APlayerState
{
	GENERATED_BODY()
public:
	AShipPlayerState();
	void Score();
	float ReceiveDamage(float Damage, AController* EventInstigator, AActor*DamageCauser);
	void ScoreGoalNode(class AShipCharacter* player);
	void ScoreKill(class AShipCharacter* player);
	void Respawn();
	void CheckEndGame();
	int32 GetScore() { return mScore; }
	UPROPERTY(EditAnywhere)
		float mMaxHealth = 100;
		

	UPROPERTY(EditAnywhere)
		float mGoalScore = 100;

	UPROPERTY(EditAnywhere)
		float mKillScore = 25;

	UPROPERTY(EditAnywhere)
		int32 mMaxScore = 1000;
private:
	int mScore;
	float mHealth;
	FTimerHandle SpawnHandle;
	
	
	
};
