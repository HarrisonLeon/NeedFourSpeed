// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/PlayerController.h"
#include "ShipCharacter.h"
#include "ShipPlayerController.generated.h"

UCLASS()
class NEEDFOURSPEED_API AShipPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AShipPlayerController();

	void PlayerTick(float DeltaTime) override;

	void SetupInputComponent() override;
	virtual void BeginPlay() override;
	void MoveForward(float Value);
	void MoveRight(float Value);
	void Blink();
	void Aim();
	void StopFire();

	void Respawn();
	void EndRespawn();

	AShipCharacter* ControlledShip;

private:
	bool mCanMove;

	FTimerHandle EndRespawnHandle;
	
};
