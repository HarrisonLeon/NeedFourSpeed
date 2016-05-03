// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.h"
#include "Weapon.generated.h"

/*
*Create our own game trace channel
*/
#define TRACE_WEAPON ECC_GameTraceChannel1

/*
*Creat an enum
*/
/*UENUM(BlueprintType)
namespace EWeaponProjectile // must define namespace for naming collision issues
{
enum ProjectileType
{
EBullet			UMETA(DisplayName = "Bullet"), //The META changes display name in editor
EProjectile		UMETA(DisplayName = "Projectile"),
};
}*/


/*
*Create a struct
*/
USTRUCT()
struct FWeaponData
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditDefaultsOnly, Category = Ammo)
		int32 mMaxAmmo;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		float mTimeBetweenShots;

	UPROPERTY(EditDefaultsOnly, Category = config)
		float mWeaponRange;

	UPROPERTY(EditDefaultsOnly, Category = config)
		float mWeaponSpread;

	UPROPERTY(EditDefaultsOnly, Category = config)
		int32 mNumBulletsPerShot;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		bool mIsAutomatic;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		bool mUnlimitedAmmo;
};


UCLASS()
class NEEDFOURSPEED_API AWeapon : public AActor
{
	GENERATED_BODY()

public:

	AWeapon();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	int32 GetCurrentAmmo() { return mNumShots; }

	UFUNCTION()
		void Fire(FVector AimDirection);

	UFUNCTION()
		virtual void StopFire();

	UFUNCTION()
		virtual void CanFireAgain();

	UFUNCTION()
		void Fire_Trace(const FVector& shootDir);

	UFUNCTION()
		virtual void Fire_Projectile(TSubclassOf<class AActor> BulletClass, const FVector& FireDirection);

	UFUNCTION()
		UAudioComponent* PlayWeaponSound(USoundCue* sound);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Collision)
	class UBoxComponent* mCollisionComp;

protected:

	int32 mNumShots;

	bool mCanFire;

	FVector mAimDir;

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class USoundCue* mFireSound;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		FWeaponData mWeaponConfig;

	UPROPERTY(EditAnywhere, Category = Config)
		TSubclassOf<class ABullet> mBulletClass;

	FHitResult WeaponTrace(const FVector& TraceFrom, const FVector& TraceTo)const;

	void ProcessInstantHit(const FHitResult& impact, const FVector& Origin, const FVector& ShootDir);
};
