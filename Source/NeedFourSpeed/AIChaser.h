// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "AICharacter.h"
#include "AIChaser.generated.h"

/**
 * 
 */
UCLASS()
class NEEDFOURSPEED_API AAIChaser : public AAICharacter
{
	GENERATED_BODY()

public:
	AAIChaser();

	// Called when the game starts or when spawned
	void BeginPlay() override;

	// Called every frame
	void Tick(float DeltaSeconds) override;

	void StartAttack() override;

	void StopAttack()override;

	void Die() override;

	void DoDamageToPlayer() override;

	UFUNCTION()
		void OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UPROPERTY(EditDefaultsOnly, Category = Collision)
		USphereComponent* mSphereComponent;

private:
	
};
