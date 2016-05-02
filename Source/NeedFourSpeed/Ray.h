// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "Bullet.h"
#include "Ray.generated.h"

UCLASS()
class NEEDFOURSPEED_API ARay : public ABullet
{
	GENERATED_BODY()

	/** Sphere collision component */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Projectile, meta = (AllowPrivateAccess = "true"))
		UStaticMeshComponent* RayMesh;
	
public:	
	// Sets default values for this actor's properties
	ARay();

	// Called when the game starts or when spawned
	void BeginPlay() override;
	
	// Called every frame
	void Tick( float DeltaSeconds ) override;

	UPROPERTY(EditDefaultsOnly,Category=Config)
		float mRayScaleSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		float mMaxXScale;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		float mRayBackSpeed;

	/** Function to handle the ray hitting something */
	UFUNCTION()
		void OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
};
