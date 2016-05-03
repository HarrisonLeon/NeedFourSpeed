// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "Engine.h"
#include "RayWeapon.h"


ARayWeapon::ARayWeapon()
{
	mWeaponConfig.mWeaponSpread = 0.0f;
	mWeaponConfig.mNumBulletsPerShot = 1;
	mWeaponConfig.mWeaponRange = 10000.0f;
	mWeaponConfig.mTimeBetweenShots = 6.0f;
	mWeaponConfig.mMaxAmmo = 3;
	mWeaponConfig.mIsAutomatic = false;
	mWeaponConfig.mUnlimitedAmmo = false;
	mNumShots = mWeaponConfig.mMaxAmmo;
}

void ARayWeapon::Fire_Projectile(TSubclassOf<class AActor> RayClass, const FVector& FireDirection)
{
	const FRotator FireRotation = FireDirection.Rotation();
	// Spawn projectile at an offset from this pawn
	const FVector SpawnLocation = GetActorLocation();

	//Check to make sure the projectile class is specified
	if (RayClass)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;
			// spawn the projectile
			ARay* projectile =
				World->SpawnActor<ARay>(RayClass, this->GetActorLocation(),
					FireRotation, spawnParams);
		}
	}
}