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
	mWeaponConfig.mMaxAmmo = 40;
	mWeaponConfig.mIsAutomatic = true;
	mWeaponConfig.mUnlimitedAmmo = false;
	mNumShots = mWeaponConfig.mMaxAmmo;
}
