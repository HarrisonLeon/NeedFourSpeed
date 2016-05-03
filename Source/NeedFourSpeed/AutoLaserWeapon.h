// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "Projectile.h"
#include "AutoLaserWeapon.generated.h"

/**
 * 
 */
UCLASS()
class NEEDFOURSPEED_API AAutoLaserWeapon : public AWeapon
{
	GENERATED_BODY()

public:
	AAutoLaserWeapon();

	void Fire(FVector AimDirection) override;

private:
	
	
};
