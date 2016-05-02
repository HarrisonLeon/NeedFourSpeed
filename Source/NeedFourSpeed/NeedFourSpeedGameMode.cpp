// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "NeedFourSpeed.h"
#include "NeedFourSpeedGameMode.h"
#include "ShipCharacter.h"
#include "ShipPlayerController.h"

ANeedFourSpeedGameMode::ANeedFourSpeedGameMode()
{
	//DefaultPawnClass = AShipCharacter::StaticClass();

	//PlayerControllerClass = AShipPlayerController::StaticClass();
	//playerStarts = TArray<APlayerStart*>();
	this->bDelayedStart = true;

}

void ANeedFourSpeedGameMode::BeginPlay()
{
	Super::BeginPlay();

	controller1 = Cast<AShipPlayerController>(UGameplayStatics::CreatePlayer(GetWorld(), 1, true));
	controller2 = Cast<AShipPlayerController>(UGameplayStatics::CreatePlayer(GetWorld(), 2, true));
	controller3 = Cast<AShipPlayerController>(UGameplayStatics::CreatePlayer(GetWorld(), 3, true));
	//controller4 = Cast<AShipPlayerController>(UGameplayStatics::CreatePlayer(GetWorld(), 4, true));

	//Cast<AShipCharacter>(controller1->GetPawn())->SetPlayerIndex(1);
	//Cast<AShipCharacter>(controller2->GetPawn())->SetPlayerIndex(2);
	//Cast<AShipCharacter>(controller3->GetPawn())->SetPlayerIndex(3);
	//controller4->SetPlayerIndex(4);

	//
	players.Add(GetWorld()->GetFirstPlayerController());
	players.Add(controller1);
	players.Add(controller2);
	players.Add(controller3);
	//players.Add(controller4);

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Instigator;
	mCustomCamera = GetWorld()->SpawnActor<ACustomCamera>(mCustomCameraClass, spawnParams);

	this->bDelayedStart = false;
}

void ANeedFourSpeedGameMode::AddPlayerIndexToSpawnQueue(int32& index)
{
	this->mSpawnQueue.Enqueue(index);
}

void ANeedFourSpeedGameMode::HandleMatchHasStarted() {
	Super::HandleMatchHasStarted();
	//Cast<AShipPlayerController>(GetWorld()->GetFirstLocalPlayerFromController())->Repossess();
	//controller1->Repossess();
	//controller2->Repossess();
	//Cast<AShipCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())->GetMesh()->Deactivate();
	//Cast<AShipCharacter>(GetWorld()->GetFirstPlayerController()->GetPawn())->InputComponent->Deactivate();
	mCustomCamera->Init(players);
}

TArray<class APlayerController*> ANeedFourSpeedGameMode::getAllPlayerControllers() {
	return players;
}

ACustomCamera* ANeedFourSpeedGameMode::GetCustomCamera() {
	return mCustomCamera;
}