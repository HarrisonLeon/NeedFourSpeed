// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "Engine.h"
#include "WeaponPickUp.h"
#include "SpawnManager.h"

void AWeaponPickUp::PickUp(AShipCharacter* player)
{
	if (player != NULL)
	{
		player->EquipWeapon(mWeaponClass);
		TArray<AActor*> manager;
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), ASpawnManager::StaticClass(), manager);
		if (manager[0]) {
			Cast<ASpawnManager>(manager[0])->RemoveWeapon(mPosition);
		}		
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("NULL player on weapon pickup"));
	}
}

void AWeaponPickUp::SetRelativePosition(int32 pos) {
	mPosition = pos;
}


