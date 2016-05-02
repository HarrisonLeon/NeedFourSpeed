// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "Engine.h"
#include "AutoLaserWeapon.h"

AAutoLaserWeapon::AAutoLaserWeapon()
{
	mWeaponConfig.mWeaponSpread = 0;
	mWeaponConfig.mNumBulletsPerShot = 1;
	mWeaponConfig.mWeaponRange = 4000.0f;
	mWeaponConfig.mTimeBetweenShots = .1f;
	mWeaponConfig.mMaxAmmo = 80;
	mWeaponConfig.mIsAutomatic = true;
	mWeaponConfig.mUnlimitedAmmo = false;
	mNumShots = mWeaponConfig.mMaxAmmo;
}

void AAutoLaserWeapon::Fire()
{
	if (mCanFire)
	{
		if (mNumShots > 0||mWeaponConfig.mUnlimitedAmmo)
		{
			Super::Fire();
			//Get the weapon config stuff
			const FVector aimDir = this->GetActorRotation().Vector();//GetSocketRotation("MF").Vector();
			const int32 numBullets = mWeaponConfig.mNumBulletsPerShot;
			const float weaponSpread = mWeaponConfig.mWeaponSpread;
			const float weaponRange = mWeaponConfig.mWeaponRange;
			const float timeBetweenShots = mWeaponConfig.mTimeBetweenShots;

			//Set timer for next shot for automatic gun
			FTimerHandle fireHandle;
			UWorld* world = GetWorld();
			if (world)
			{
				//Set timer
				world->GetTimerManager().SetTimer(fireHandle, this, &AAutoLaserWeapon::Fire, timeBetweenShots);
			}
			Fire_Projectile(mBulletClass, mAimDir);
		}
	}
	else
	{
		mCanFire = true;
	}
}


