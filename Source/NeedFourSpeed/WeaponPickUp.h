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
	void SetRelativePosition(int32 pos);
	UPROPERTY(EditDefaultsOnly, Category = Spawn)
		TSubclassOf<class AWeapon> mWeaponClass;
	
private:
	TArray<int32>* mExistingWeapon;
	int32 mPosition;

};