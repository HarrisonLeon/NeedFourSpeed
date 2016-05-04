// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ActorEmitter.generated.h"

UCLASS()
class NEEDFOURSPEED_API AActorEmitter : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AActorEmitter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditDefaultsOnly, Category = Spawn)
		float mSpawnGap;

	UPROPERTY(EditDefaultsOnly, Category = Spawn)
		TSubclassOf<class AActor> mActorClass;
private:

	void SpawnNewActor();
	
};
