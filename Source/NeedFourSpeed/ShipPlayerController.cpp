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
		//InputComponent->BindAxis("FireForward", this, &AShipPlayerController::Fire);
		//InputComponent->BindAxis("FireRight", this, &AShipPlayerController::Fire);
		InputComponent->BindAction("Fire", IE_Pressed, this, &AShipPlayerController::Fire);
		InputComponent->BindAction("Fire", IE_Released, this, &AShipPlayerController::StopFire);
		InputComponent->BindAction("Dash", IE_Pressed, this, &AShipPlayerController::Dash);
	}
}

void AShipPlayerController::MoveForward(float Value)
{
	/*if (ControlledShip && Value != 0.0f)
	{
	ControlledShip->MoveForward(Value);
	}*/
	if (Cast<AShipCharacter>(GetPawn()) && Value != 0.0f) {
		Cast<AShipCharacter>(GetPawn())->MoveForward(Value);
	}

}

void AShipPlayerController::MoveRight(float Value)
{
	/*if (ControlledShip && Value != 0.0f)
	{
	ControlledShip->MoveRight(Value);
	}*/
	if (Cast<AShipCharacter>(GetPawn()) && Value != 0.0f) {
		Cast<AShipCharacter>(GetPawn())->MoveRight(Value);
	}
}

void AShipPlayerController::Aim()
{
	const float AimForwardValue = GetInputAxisValue("AimForward");
	const float AimRightValue = GetInputAxisValue("AimRight");

	/*if (ControlledShip)
	{
	ControlledShip->Aim(AimForwardValue, AimRightValue);
	}*/
	if (Cast<AShipCharacter>(GetPawn())) {
		Cast<AShipCharacter>(GetPawn())->Aim(AimForwardValue, AimRightValue);
	}
}

void AShipPlayerController::AimForward(float Value)
{
	/*if (ControlledShip && Value != 0.0f)
	{
	ControlledShip->AimForward(Value);
	}*/
	if (Cast<AShipCharacter>(GetPawn()) && Value != 0.0f) {
		Cast<AShipCharacter>(GetPawn())->AimForward(Value);
	}
}

void AShipPlayerController::AimRight(float Value)
{
	/*if (ControlledShip && Value != 0.0f)
	{
	ControlledShip->AimRight(Value);
	}*/
	if (Cast<AShipCharacter>(GetPawn()) && Value != 0.0f) {
		Cast<AShipCharacter>(GetPawn())->AimRight(Value);
	}
}

void AShipPlayerController::Fire()
{
	/*if (ControlledShip) {
	ControlledShip->Fire();
	}*/
	if (Cast<AShipCharacter>(GetPawn())) {
		Cast<AShipCharacter>(GetPawn())->Fire();
	}
}

void AShipPlayerController::StopFire()
{
	/*if (ControlledShip) {
	ControlledShip->StopFire();
	}*/
	if (Cast<AShipCharacter>(GetPawn())) {
		Cast<AShipCharacter>(GetPawn())->StopFire();
	}
}

void AShipPlayerController::Dash()
{
	if (Cast<AShipCharacter>(GetPawn())) {
		Cast<AShipCharacter>(GetPawn())->Dash();
	}
}

void AShipPlayerController::Repossess() {
	//ControlledShip = Cast<AShipCharacter>(GetPawn());
}


