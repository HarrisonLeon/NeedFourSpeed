// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "ShipCharacter.h"
#include "Weapon.h"
#include "WeaponPickUp.generated.h"

/**
*
*/
UCLASS()
class NEEDFOURSPEED_API AWeaponPickUp : public APickUp
{
	GENERATED_BODY()

public:

	void PickUp(AShipCharacter* player) override;

	UPROPERTY(EditDefaultsOnly, Category = Spawn)
		TSubclassOf<class AWeapon> mWeaponClass;

};