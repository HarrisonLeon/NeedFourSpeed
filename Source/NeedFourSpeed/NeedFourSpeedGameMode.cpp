// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.

#include "NeedFourSpeed.h"
#include "NeedFourSpeedGameMode.h"
#include "ShipCharacter.h"
#include "ShipPlayerController.h"

ANeedFourSpeedGameMode::ANeedFourSpeedGameMode()
{
	PlayerControllerClass = AShipPlayerController::StaticClass();
	this->bDelayedStart = true;
}

void ANeedFourSpeedGameMode::BeginPlay()
{
	Super::BeginPlay();

	players.Add(GetWorld()->GetFirstPlayerController());

	for (int i = 1; i <= mNumPlayer; i++) {
		AShipPlayerController* controller = Cast<AShipPlayerController>(UGameplayStatics::CreatePlayer(GetWorld(), i, true));
		players.Add(controller);
	}

	//players.Add(GetWorld()->GetFirstPlayerController());

	this->bDelayedStart = false;
}

void ANeedFourSpeedGameMode::AddPlayerIndexToSpawnQueue(int32& index)
{
	this->mSpawnQueue.Enqueue(index);
}

void ANeedFourSpeedGameMode::HandleMatchHasStarted() {
	Super::HandleMatchHasStarted();

	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = Instigator;
	mCustomCamera = GetWorld()->SpawnActor<ACustomCamera>(mCustomCameraClass, spawnParams);

	TArray<AActor*> allActor;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AShipCharacter::StaticClass(), allActor);
	int32 index = 0;
	float maxHeight = 0.0f;
	for (int i = 0; i < allActor.Num(); i++) {
		AShipCharacter* pawn = Cast<AShipCharacter>(allActor[i]);
		if (!Cast<APlayerController>(pawn->GetController())){
			index = i;
			maxHeight = pawn->GetActorLocation().Z;
		}
	}
	AActor* pawn = allActor[index];
	if (pawn) {
		FVector defaultPlayerLoc = pawn->GetRootComponent()->GetComponentLocation();
		defaultPlayerLoc.Z -= 9999999999999999999999999999999999.0f;
		pawn->SetActorLocation(defaultPlayerLoc, false);
	}
	mCustomCamera->Init(players);
}

TArray<class APlayerController*> ANeedFourSpeedGameMode::getAllPlayerControllers() {
	return players;
}

ACustomCamera* ANeedFourSpeedGameMode::GetCustomCamera() {
	return mCustomCamera;
}

void ANeedFourSpeedGameMode::SetPlayerNum(int32 num) {
	mNumPlayer = num;
}