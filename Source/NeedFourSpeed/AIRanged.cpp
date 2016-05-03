// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "AIRanged.h"
#include "AIRangedController.h"

// Sets default values
AAIRanged::AAIRanged()
{
	AIControllerClass = AAIRangedController::StaticClass();
}

// Called when the game starts or when spawned
void AAIRanged::BeginPlay()
{
	Super::BeginPlay();
	//Spawn current weapon on AI
	EquipWeapon(mWeaponClass);
}

// Called every frame
void AAIRanged::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIRanged::StartAttack()
{
	GetWorldTimerManager().SetTimer(mAttackTimerHandle, this, &AAIRanged::StartAttack, 1.0f, true);
	if (mCurrentWeapon)
	{
		FVector AimDirection = GetActorForwardVector();
		AimDirection.Normalize();
		//mCurrentWeapon->Fire(AimDirection);
	}
}

void AAIRanged::DoDamageToPlayer()
{

}

void AAIRanged::StopAttack()
{
	GetWorld()->GetTimerManager().ClearTimer(mAttackTimerHandle);
}

void AAIRanged::Die()
{
	Super::Die();
}

void AAIRanged::EquipWeapon(TSubclassOf<class AWeapon> WeaponClass)
{
	mWeaponClass = WeaponClass;
	//Spawn the player's weapon
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = this;
	AWeapon * spawnedWeapon = GetWorld()->SpawnActor<AWeapon>(mWeaponClass, spawnParams);
	if (spawnedWeapon)
	{
		spawnedWeapon->AttachRootComponentTo(mAIMeshComponent, FName(TEXT("NAME_None")), EAttachLocation::SnapToTarget);
		if (mCurrentWeapon)
		{
			AWeapon* oldWeapon = mCurrentWeapon;
			mCurrentWeapon = NULL;
			oldWeapon->Destroy();
		}
		mCurrentWeapon = spawnedWeapon;
	}
}



