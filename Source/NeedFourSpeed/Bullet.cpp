// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "ShipCharacter.h"
#include "AICharacter.h"
#include "Engine.h"
#include "Bullet.h"


// Sets default values
ABullet::ABullet()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mLifeTime = 4.0f;
}

// Called when the game starts or when spawned
void ABullet::BeginPlay()
{
	Super::BeginPlay();
	//Set timer for death
	FTimerHandle lifeHandle;
	UWorld* world = GetWorld();
	if (world)
	{
		//Set timer
		world->GetTimerManager().SetTimer(lifeHandle, this, &ABullet::Kill, mLifeTime);
	}
}

// Called every frame
void ABullet::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ABullet::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	//Create the muzzle flash
	//MuzzleFXAC=UGameplayStatics::SpawnEmitterAtLocation(this, mHitEffect, SweepResult.ImpactPoint);
	UGameplayStatics::SpawnEmitterAtLocation(this, mHitEffect, SweepResult.ImpactPoint);
}

void ABullet::Kill()
{
	Destroy();
}