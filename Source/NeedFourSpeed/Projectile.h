// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.h"
#include "Engine.h"
#include "Projectile.generated.h"


UCLASS()
class NEEDFOURSPEED_API AProjectile : public ABullet
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* ProjectileMesh;

	/** Projectile movement component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Movement, meta = (AllowPrivateAccess = "true"))
		UProjectileMovementComponent* ProjectileMovement;

public:
	// Sets default values for this actor's properties
	AProjectile();

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaSeconds) override;

	/** Function to handle the projectile hitting something */
	UFUNCTION()
		void OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = Collision)
		UCapsuleComponent* mCapsuleComponent;

	/** Returns ProjectileMovement subobject **/
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovement() const { return ProjectileMovement; }



};
