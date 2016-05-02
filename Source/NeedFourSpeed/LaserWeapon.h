// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "LaserWeapon.generated.h"

/**
*
*/
UCLASS()
class NEEDFOURSPEED_API ALaserWeapon : public AWeapon
{
	GENERATED_BODY()

public:

	ALaserWeapon();

	void Fire() override;
};
