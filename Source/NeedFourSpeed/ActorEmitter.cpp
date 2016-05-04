// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "ActorEmitter.h"


// Sets default values
AActorEmitter::AActorEmitter()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AActorEmitter::BeginPlay()
{
	Super::BeginPlay();
	SpawnNewActor();
}

// Called every frame
void AActorEmitter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void AActorEmitter::SpawnNewActor()
{
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	AActor * spawnedActor = GetWorld()->SpawnActor<AActor>(mActorClass,this->GetActorLocation(),this->GetActorRotation(),spawnParams);
	if (spawnedActor)
	{
		FTimerHandle timerHandle;
		//Set timer
		UWorld* World = GetWorld();
		if (World)
		{
			World->GetTimerManager().SetTimer(timerHandle, this, &AActorEmitter::SpawnNewActor, this->mSpawnGap);
		}
	}
}

