// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "Engine.h"
#include "ScatterLaser.h"

AScatterLaser::AScatterLaser()
{
	mWeaponConfig.mWeaponSpread = 60.0f;
	mWeaponConfig.mNumBulletsPerShot = 4;
	mWeaponConfig.mWeaponRange = 1500.0f;
	mWeaponConfig.mTimeBetweenShots = 2.0f;
	mWeaponConfig.mMaxAmmo = 40;
	mWeaponConfig.mIsAutomatic = false;
	mWeaponConfig.mUnlimitedAmmo = false;
	mNumShots = mWeaponConfig.mMaxAmmo;
}

void AScatterLaser::Fire()
{
	if (mNumShots > 0 || mWeaponConfig.mUnlimitedAmmo)
	{
		Super::Fire();
		//Get the weapon config stuff//GetSocketRotation("MF").Vector();
		const int32 numBullets = mWeaponConfig.mNumBulletsPerShot;
		const float weaponSpread = mWeaponConfig.mWeaponSpread;
		const float weaponRange = mWeaponConfig.mWeaponRange;
		const float timeBetweenShots = mWeaponConfig.mTimeBetweenShots;

		//Calculate the space in between each shot
		float shotSpacing = weaponSpread / (numBullets + 1);
		//Change aimDir to be far left so we can move from left to right spawning bullets
		FVector rotatedAimDir = mAimDir.RotateAngleAxis(-weaponSpread / 2, FVector(0, 0, 1));
		for (int32 i = 1; i <= numBullets; i++)
		{
			FVector actualAimDir = rotatedAimDir.RotateAngleAxis(shotSpacing*i, FVector(0, 0, 1));
			Fire_Projectile(mBulletClass, actualAimDir);
		}
	}
}


