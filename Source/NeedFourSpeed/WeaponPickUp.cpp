// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "Engine.h"
#include "WeaponPickUp.h"

void AWeaponPickUp::PickUp(AShipCharacter* player)
{
	if (player != NULL)
	{
		player->EquipWeapon(mWeaponClass);
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 2.f, FColor::Black, TEXT("NULL player on weapon pickup"));
	}
}


