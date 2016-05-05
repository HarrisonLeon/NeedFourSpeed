// Copyright 1998-2015 Epic Games, Inc. All Rights Reserved.
#pragma once

#include "GameFramework/GameMode.h"
#include "CustomCamera.h"
#include "NeedFourSpeedGameMode.generated.h"


UCLASS()
class NEEDFOURSPEED_API ANeedFourSpeedGameMode : public AGameMode
{
	GENERATED_BODY()

public:
	ANeedFourSpeedGameMode();

	void BeginPlay() override;

	void HandleMatchHasStarted() override;
	ACustomCamera* GetCustomCamera();
	TArray<class APlayerController*> getAllPlayerControllers();

	UPROPERTY(EditDefaultsOnly, Category = Camera)
		TSubclassOf<ACustomCamera> mCustomCameraClass;

	//this function is used for spawning player with correct index 
	void AddPlayerIndexToSpawnQueue(int32& index);
	void SetPlayerNum(int32 num);
	TQueue<int32>& GetPlayerIndexSpawnQueue() { return mSpawnQueue; }

	//UPROPERTY(EditAnywhere, Category = Location)
	//TArray<APlayerStart*> playerStarts;
	UPROPERTY(EditAnywhere)
		int32 mNumPlayer = 3;
private:
	//class AShipPlayerController* controller0;
	/*class AShipPlayerController* controller1;
	AShipPlayerController* controller2;
	AShipPlayerController* controller3;
	AShipPlayerController* controller4;*/
	TArray<class APlayerController*> players;
	class ACustomCamera* mCustomCamera;
	TQueue<int32> mSpawnQueue;

};



