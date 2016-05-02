// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Actor.h"
#include "ShipCharacter.h"
#include "PickUp.generated.h"

UCLASS()
class NEEDFOURSPEED_API APickUp : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	APickUp();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	/** Function to handle the projectile hitting something */
	UFUNCTION()
		void OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
		void OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	virtual void PickUp(AShipCharacter* player);

private:

	UPROPERTY(EditDefaultsOnly, Category = Effects)
	class UParticleSystemComponent* mParticleSystem;

	UPROPERTY(EditDefaultsOnly, Category = Effects)
	class USoundCue* mPickUpSound;

	UPROPERTY(EditDefaultsOnly, Category = Config)
		float mRotationSpeed;

	UPROPERTY(EditDefaultsOnly, Category = Collision)
		USphereComponent* mSphereComponent;

	UPROPERTY(EditDefaultsOnly, Category = PickUp)
		USkeletalMeshComponent* mPickUpMesh;
};
