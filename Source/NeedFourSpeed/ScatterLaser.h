// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "Weapon.h"
#include "ScatterLaser.generated.h"

/**
 * 
 */
UCLASS()
class NEEDFOURSPEED_API AScatterLaser : public AWeapon
{
	GENERATED_BODY()
	
public:

	AScatterLaser();

	virtual void Fire() override;
};
