// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "Ray.h"
#include "RayWeapon.generated.h"

/**
*
*/
UCLASS()
class NEEDFOURSPEED_API ARayWeapon : public AWeapon
{
	GENERATED_BODY()

public:

	ARayWeapon();

	void Fire() override;

	void Fire_Projectile(TSubclassOf<class AActor> ProjectileClass, const FVector& FireDirection);
};
