// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "Engine.h"
#include "Bullet.h"
#include "ShipCharacter.h"
#include "NeedFourSpeedProjectile.h"
#include "Weapon.h"

AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mCollisionComp = CreateDefaultSubobject<UBoxComponent>(TEXT("CollisionComp"));
	RootComponent = mCollisionComp;

	//Make the weapon mesh ignore all collision
	mCollisionComp->bGenerateOverlapEvents=false;

	//mWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SkeletalMesh"));
	//mWeaponMesh->AttachTo(RootComponent);
	mCanFire = true;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

/*Fire weapon based on the type*/
void AWeapon::Fire(FVector AimDirection)
{
	//FString boolString = mCanFire ? "I CAN SHOOT" : "NO WAY";
	//GEngine->AddOnScreenDebugMessage(-1, 15.0f, FColor::Red, boolString);

	if (mCanFire)
	{
		if (mNumShots > 0 || mWeaponConfig.mUnlimitedAmmo)
		{
			mNumShots--;
			mAimDir = AimDirection;
			

			//Subtract ammo from hud if it is a player
			//Draw ammo to HUD
			if (Instigator->IsA(AShipCharacter::StaticClass()))
			{
				AShipCharacter* player = Cast<AShipCharacter>(Instigator);
				if (player)
				{
					player->SetPlayerAmmo(GetCurrentAmmo());
				}
			}

			//Set timer for next shot for automatic gun
			mCanFire = false;

			Fire_Projectile(mBulletClass, AimDirection);

			FTimerHandle fireHandle;
			UWorld* World = GetWorld();
			if (World)
			{
				//Set timer
				World->GetTimerManager().SetTimer(fireHandle, this, &AWeapon::CanFireAgain, mWeaponConfig.mTimeBetweenShots);
			}

			PlayWeaponSound(mFireSound);

			mCanFire = false;
		}
	}
}

void AWeapon::StopFire()
{
	mCanFire = false;
}

void AWeapon::CanFireAgain()
{
	mCanFire = true;
}

/*Fire a projectile*/
void AWeapon::Fire_Projectile(TSubclassOf<class AActor> BulletClass, const FVector& FireDirection)
{
	const FRotator FireRotation = FireDirection.Rotation();
	// Spawn projectile at an offset from this pawn
	const FVector SpawnLocation = GetActorLocation();

	//Check to make sure the projectile class is specified
	if (BulletClass)
	{
		UWorld* const World = GetWorld();
		if (World != NULL)
		{
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;
			spawnParams.Instigator = Instigator;
			// spawn the projectile
			ABullet* bullet =
				World->SpawnActor<ABullet>(BulletClass, this->GetActorLocation(),
					FireRotation, spawnParams);
		}
	}
}

/*Fire a tracer*/
void AWeapon::Fire_Trace(const FVector& shootDir)
{
	const float weaponSpread = mWeaponConfig.mWeaponSpread;
	const float weaponRange = mWeaponConfig.mWeaponRange;
	const int32 numBullets = mWeaponConfig.mNumBulletsPerShot;
	const FVector startTrace = this->GetActorLocation();//mWeaponMesh->GetSocketLocation("MF");
	const FVector endTrace = startTrace + (weaponRange*shootDir);
	const FHitResult impact = WeaponTrace(startTrace, endTrace);

	ProcessInstantHit(impact, startTrace, shootDir);
}

/*Draw a weapon trace*/
FHitResult AWeapon::WeaponTrace(const FVector& traceFrom, const FVector& traceTo)const
{
	//Get a collision query
	static FName weaponFireTag = FName(TEXT("WeaponTrace"));
	FCollisionQueryParams traceParams(weaponFireTag, true, Instigator);
	traceParams.bTraceAsyncScene = true;
	traceParams.bReturnPhysicalMaterial = true;
	traceParams.AddIgnoredActor(this);

	//Forceably remake line
	FHitResult hit(ForceInit);

	GetWorld()->LineTraceSingleByChannel(hit, traceFrom, traceTo, TRACE_WEAPON, traceParams);

	return hit;
}

/*Process a weapon trace hit*/
void AWeapon::ProcessInstantHit(const FHitResult& impact, const FVector& origin, const FVector& ShootDir)
{
	const FVector endTrace = origin + ShootDir*mWeaponConfig.mWeaponRange;
	const FVector endPoint = impact.GetActor() ? impact.ImpactPoint : endTrace;
	DrawDebugLine(this->GetWorld(), origin, impact.TraceEnd, FColor::Red, false, 2000,90.0f,20.0f);
}

UAudioComponent* AWeapon::PlayWeaponSound(USoundCue* sound)
{
	UAudioComponent* AC = NULL;
	if (sound)
	{
		AC = UGameplayStatics::SpawnSoundAttached(sound, RootComponent);
		AC->bStopWhenOwnerDestroyed = false;
	}
	return AC;
}

