// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "GoalNode.h"
#include "WeaponPickUp.h"
#include "SpawnManager.h"
#include "AICharacter.h"


// Sets default values
ASpawnManager::ASpawnManager()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	prevIndex = -1;
	prevWeaponIndex = -1;

}

// Called when the game starts or when spawned
void ASpawnManager::BeginPlay()
{
	Super::BeginPlay();
	SpawnGoalNode();
	//SpawnAIEnemies();
	FTimerHandle WeaponHandle;
	FTimerHandle AIHandle;
	GetWorldTimerManager().SetTimer(WeaponHandle, this, &ASpawnManager::SpawnWeapon, 2.0f, true);
	GetWorldTimerManager().SetTimer(AIHandle, this, &ASpawnManager::SpawnAIEnemies, 5.0f, true);
	
}

// Called every frame
void ASpawnManager::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

void ASpawnManager::SpawnGoalNode()
{
	int Num = goalNodeArray.Num();
	if (Num != 0) {
		int Index = FMath::RandRange(0, Num - 1);
		while (Index == prevIndex) {
			Index = FMath::RandRange(0, Num - 1);			
		}
		prevIndex = Index;
		if (goalNodeArray[Index]) {
			FVector pos = goalNodeArray[Index]->GetActorLocation();
			FRotator rot = goalNodeArray[Index]->GetActorRotation();

			// Spawn an ACharacter of subclass CharacterClass, at specified position and rotation 
			AGoalNode* Char = GetWorld()->SpawnActor<AGoalNode>(goalNodeClass, pos, rot);
			if (Char) {
				Char->SetSpawnManager(this);
			}
		}
	}
}

void ASpawnManager::SpawnWeapon() {
	int Num = weaponLoc.Num();
	if (Num != 0) {
		int Index = FMath::RandRange(0, Num - 1);
		if (weaponLoc[Index]) {
			FVector pos = weaponLoc[Index]->GetActorLocation();
			FRotator rot = weaponLoc[Index]->GetActorRotation();

			int weaponIndex = FMath::RandRange(0, weaponClass.Num() - 1);
			// Spawn an ACharacter of subclass CharacterClass, at specified position and rotation 
			AWeaponPickUp* Char = GetWorld()->SpawnActor<AWeaponPickUp>(weaponClass[weaponIndex], pos, rot);
			if (Char) {
				// Spawn the AI controller for the character 
				//Char->SpawnDefaultController();
			}
		}
	}
}

void ASpawnManager::SpawnAIEnemies() {
	int Num = AILoc.Num();
	if (Num != 0) {
		int Index = FMath::RandRange(0, Num - 1);
		if (AILoc[Index]) {
			FVector pos = AILoc[Index]->GetActorLocation();
			FRotator rot = AILoc[Index]->GetActorRotation();

			int AIIndex = FMath::RandRange(0, AIClass.Num() - 1);
			// Spawn an ACharacter of subclass CharacterClass, at specified position and rotation 
			AAICharacter* Char = GetWorld()->SpawnActor<AAICharacter>(AIClass[AIIndex], pos, rot);
			if (Char) {
				// Spawn the AI controller for the character 
				Char->SpawnDefaultController();
			}
		}
	}
}

