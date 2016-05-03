// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "LaserWeapon.h"

ALaserWeapon::ALaserWeapon()
{
	mWeaponConfig.mWeaponSpread = 0;
	mWeaponConfig.mNumBulletsPerShot = 1;
	mWeaponConfig.mWeaponRange = 4000.0f;
	mWeaponConfig.mTimeBetweenShots = 1.0f;
	mWeaponConfig.mMaxAmmo = 38;
	mWeaponConfig.mIsAutomatic = false;
	mWeaponConfig.mUnlimitedAmmo = false;
	mNumShots = mWeaponConfig.mMaxAmmo;
}
