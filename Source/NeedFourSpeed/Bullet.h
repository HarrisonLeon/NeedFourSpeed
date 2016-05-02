// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.generated.h"

UCLASS()
class NEEDFOURSPEED_API ABullet : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ABullet();

	// Called when the game starts or when spawned
	virtual void BeginPlay();

	// Called every frame
	virtual void Tick(float DeltaSeconds);

	void Kill();

	/** Function to handle the projectile hitting something */
	UFUNCTION()
		virtual void OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = Config)
		float mLifeTime;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		float mDamage;

private:

	AActor* mInstigator;

	UPROPERTY(EditDefaultsOnly)
		UParticleSystem* mHitEffect;

	UPROPERTY(Transient)
		class UParticleSystemComponent* MuzzleFXAC;

};
