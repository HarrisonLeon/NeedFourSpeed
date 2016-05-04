// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Camera/CameraActor.h"
#include "CustomCamera.generated.h"

/**
*
*/
UCLASS()
class NEEDFOURSPEED_API ACustomCamera : public ACameraActor
{
	GENERATED_BODY()

public:
	ACustomCamera(const FObjectInitializer& ObjectInitializer);
	void Init(TArray<APlayerController*> &playerArr);
	void BeginPlay() override;
	void Tick(float deltaTime) override;
	float FindLargestDistBetPlayers();
	void AdjustBoomDistance(float deltaTime);
	void StopTrackingPlayer(APlayerController* playerController);
	void StartTrackingPlayer(APlayerController* playerController);
	void StopTracking(APlayerController* playerController);
	void StartTracking(APlayerController* playerController);
	void ClearAllPlayers();

private:
	//Target just for testing
	UPROPERTY(EditAnywhere)
		TArray<APlayerController*> mPlayerArr;

	UPROPERTY(EditAnywhere)
		float mBoomDistance = 2000.0f;

	UPROPERTY(EditAnywhere)
		double mZoomThreshold = 5.0;

	UPROPERTY(EditAnywhere)
		double mZoomThreshold2 = 5.5;

	UPROPERTY(EditAnywhere)
		float mBoomMaxZoomOut = 10000.0f;

	UPROPERTY(EditAnywhere)
		float mBoomMaxZoomIn = 600.0f;

	UPROPERTY(EditAnywhere)
		float mZoomSpeed = .24f;
};
