// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AICharacter.h"
#include "AIRanged.generated.h"

/**
 * 
 */
UCLASS()
class NEEDFOURSPEED_API AAIRanged : public AAICharacter
{
	GENERATED_BODY()

public:
	AAIRanged();

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaSeconds) override;

	void StartAttack() override;

	void StopAttack()override;

	void Die() override;

	void DoDamageToPlayer() override;

private:
	void EquipWeapon(TSubclassOf<class AWeapon> WeaponClass);

	//Weapon stuff
	UPROPERTY(EditDefaultsOnly, Category = Spawn)
		TSubclassOf<class AWeapon> mWeaponClass;

	AWeapon* mCurrentWeapon;

	FTimerHandle mAttackTimerHandle;
	
	
	
};
