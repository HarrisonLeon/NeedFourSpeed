// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "ShipPlayerController.h"

#define print(text) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, FColor::Green, text)

AShipPlayerController::AShipPlayerController()
{
	//mPlayerIndex = -1;
}

void AShipPlayerController::BeginPlay()
{
	Super::BeginPlay();
	//ControlledShip = Cast<AShipCharacter>(GetPawn());
}

void AShipPlayerController::PlayerTick(float DeltaTime)
{
	Super::PlayerTick(DeltaTime);
	Aim();
}

void AShipPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	if (InputComponent)
	{
		InputComponent->BindAxis("MoveForward", this, &AShipPlayerController::MoveForward);
		InputComponent->BindAxis("MoveRight", this, &AShipPlayerController::MoveRight);
		InputComponent->BindAxis("AimForward");
		InputComponent->BindAxis("AimRight");
		InputComponent->BindAction("Dash", IE_Pressed, this, &AShipPlayerController::Dash);
	}
}

void AShipPlayerController::MoveForward(float Value)
{
	if (Cast<AShipCharacter>(GetPawn()) && Value != 0.0f) {
		Cast<AShipCharacter>(GetPawn())->MoveForward(Value);
	}

}

void AShipPlayerController::MoveRight(float Value)
{
	if (Cast<AShipCharacter>(GetPawn()) && Value != 0.0f) {
		Cast<AShipCharacter>(GetPawn())->MoveRight(Value);
	}
}

void AShipPlayerController::Aim()
{
	const float AimForwardValue = GetInputAxisValue("AimForward");
	const float AimRightValue = GetInputAxisValue("AimRight");

	if (Cast<AShipCharacter>(GetPawn())) {
		Cast<AShipCharacter>(GetPawn())->Aim(AimForwardValue, AimRightValue);
	}
}

void AShipPlayerController::StopFire()
{}

void AShipPlayerController::Dash()
{
	if (Cast<AShipCharacter>(GetPawn())) {
		Cast<AShipCharacter>(GetPawn())->Dash();
	}
}


