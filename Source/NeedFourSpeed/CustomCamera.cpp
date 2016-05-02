// Fill out your copyright notice in the Description page of Project Settings.
#include "NeedFourSpeed.h"
#include "UnrealMath.h"
#include "Engine.h"
#include "ShipCharacter.h"
#include "CustomCamera.h"

ACustomCamera::ACustomCamera(const FObjectInitializer& ObjectInitializer) : ACameraActor(ObjectInitializer)
{


}

void ACustomCamera::Init(TArray<APlayerController*>& playerControllers)
{
	for (auto& controller : playerControllers)
	{
		mPlayerArr.Add(controller);
	}
}

void ACustomCamera::StopTrackingPlayer(APlayerController* playerController)
{
	if (playerController)
	{
		mPlayerArr.Remove(playerController);
	}
}

void ACustomCamera::StartTrackingPlayer(APlayerController* playerController)
{
	if (playerController)
	{
		mPlayerArr.Add(playerController);
	}
}

void ACustomCamera::BeginPlay()
{
	

	//Set rotation of the camera to face downwards
	FVector vect(0, 0, -1);
	FRotator rot = vect.Rotation();
	SetActorRotation(rot);
}

void ACustomCamera::Tick(float deltaTime)
{
	if (mPlayerArr.Num() <= 0) return;

	//Set the current camera view to be this camera's
	for (auto& controller : mPlayerArr)
	{
		if (controller)
		{
			if (controller->GetViewTarget() != this){
				controller->SetViewTarget(this);
			}
		}
		else
		{
			GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("Camera cannot attach to null controller"));
		}
	}

	//Find average location between all players
	FVector posSums = FVector::ZeroVector;

	//Find average location between players
	for (int i = 0; i < mPlayerArr.Num(); i++)
	{
		AShipCharacter* currPlayer = Cast<AShipCharacter>(mPlayerArr[i]->GetPawn());
		if (currPlayer != NULL)
		{
			posSums += currPlayer->GetActorLocation();
		}
	}
	FVector averageLoc = posSums / float(mPlayerArr.Num());
	averageLoc.Z = 0;

	//Adjust the boom so we can see all players well
	AdjustBoomDistance(deltaTime);

	//Set camera position based on calculations
	FVector boomUp(0, 0, 1); 

	//Get a position of the camera without height
	FVector xyCamPos = this->GetActorLocation();
	xyCamPos.Z = 0;
	averageLoc = FMath::Lerp(xyCamPos, averageLoc, 2*deltaTime);
	this->SetActorLocation(averageLoc + (boomUp*mBoomDistance));
}

void ACustomCamera::AdjustBoomDistance(float deltaTime)
{
	//Change boom distance based on how far away players are from each other
	float largestDist = FindLargestDistBetPlayers();
	double fieldOfView = this->GetCameraComponent()->FieldOfView;
	double cameraViewDist = tan(fieldOfView / 2)*mBoomDistance * 2; //Gets the amount of ground the camera can see
																	//If camera cannot see the players it must zoom out
	if (largestDist > cameraViewDist / mZoomThreshold)
	{
		//Check to make sure we don't zoom out too far
		mBoomDistance = FMath::FInterpTo(mBoomDistance, mBoomMaxZoomOut, deltaTime, mZoomSpeed);
	}
	else if (largestDist <= cameraViewDist / mZoomThreshold2) //If the camera is zoomed out too far then zoom in
	{
		//Check to make sure we don't zoom in too much
		mBoomDistance = FMath::FInterpTo(mBoomDistance, mBoomMaxZoomIn, deltaTime, mZoomSpeed);
	}
	//Clamp zoom (doens't zoom in or out too far)
	FMath::Clamp(mBoomDistance, mBoomMaxZoomIn, mBoomMaxZoomOut);
}

float ACustomCamera::FindLargestDistBetPlayers()
{
	float largestDist = 0;
	for (int i = 0; i < mPlayerArr.Num(); i++)
	{
		AShipCharacter* currPlayer = Cast<AShipCharacter>(mPlayerArr[i]->GetPawn());
		for (int j = 0; j < mPlayerArr.Num(); j++)
		{
			AShipCharacter* otherPlayer = Cast<AShipCharacter>(mPlayerArr[j]->GetPawn());
			if (currPlayer&&otherPlayer)
			{
				//Check next player if we are trying to check distance with ourself
				if (currPlayer == otherPlayer)
				{
					continue;
				}
				float distanceSquared = (currPlayer->GetActorLocation() - otherPlayer->GetActorLocation()).SizeSquared();
				if (distanceSquared > largestDist)
				{
					largestDist = distanceSquared;
				}
			}
		}
	}
	return sqrt(largestDist);
}

void ACustomCamera::StopTracking(APlayerController* playerController) {
	mPlayerArr.Remove(playerController);
}

void ACustomCamera::StartTracking(APlayerController* playerController) {
	mPlayerArr.Add(playerController);
}

