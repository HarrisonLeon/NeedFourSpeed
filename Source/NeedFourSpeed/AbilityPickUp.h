// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "PickUp.h"
#include "ShipCharacter.h"
#include "Ability.h"
#include "AbilityPickUp.generated.h"

/**
 * 
 */
UCLASS()
class NEEDFOURSPEED_API AAbilityPickUp : public APickUp
{
	GENERATED_BODY()
	
	void PickUp(AShipCharacter* player) override;

	UPROPERTY(EditDefaultsOnly, Category = Spawn)
		TSubclassOf<class AAbility> mAbilityClass;
	
	
};
