// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "SpawnManager.generated.h"

UCLASS()
class NEEDFOURSPEED_API ASpawnManager : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawnManager();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	// Called every frame
	virtual void Tick( float DeltaSeconds ) override;

	void SpawnGoalNode();
	void SpawnWeapon();
	void SpawnAIEnemies();
	void RemoveWeapon(int32 pos);
protected:
	UPROPERTY(EditAnywhere)
		TArray<class ATargetPoint*> goalNodeArray;
	UPROPERTY(EditAnywhere)
		TSubclassOf<class AGoalNode> goalNodeClass;

	//array of weapon pick up blueprints
	UPROPERTY(EditAnywhere)
		TArray<class ATargetPoint*> weaponLoc;
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class AWeaponPickUp>> weaponClass;
	
	//array of AI spawning
	UPROPERTY(EditAnywhere)
		TArray<class ATargetPoint*> AILoc;
	UPROPERTY(EditAnywhere)
		TArray<TSubclassOf<class AAICharacter> > AIClass;

private:
	int prevIndex;
	int prevWeaponIndex;
	TArray<int32> existingWeapon;
	
	
	
};
