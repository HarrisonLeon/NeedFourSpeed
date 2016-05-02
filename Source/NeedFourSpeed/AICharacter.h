// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Bullet.h"
#include "Weapon.h"
#include "AICharacter.generated.h"

UCLASS()
class NEEDFOURSPEED_API AAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AAICharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay();
	
	// Called every frame
	virtual void Tick( float DeltaSeconds );

	// Called to bind functionality to input
	void SetupPlayerInputComponent(class UInputComponent* InputComponent);
	
	float ApplyDamage(float Damage, AActor*DamageCauser);

	virtual void StartAttack();

	virtual void StopAttack();

	virtual void Die();

	virtual void DoDamageToPlayer();

	float ReceiveDamage(float Damage, AController* EventInstigator, AActor*DamageCauser);

	/* The mesh component */
	UPROPERTY(EditDefaultsOnly, Category=MeshComponent)
		class UStaticMeshComponent* mAIMeshComponent;

	/*UPROPERTY(EditDefaultsOnly, Category=Mesh)
		class UStaticMesh * mAIMesh;*/

private:

	UPROPERTY(EditAnywhere, Category = Health)
		float mHealth = 40.0f;
	UPROPERTY(EditAnywhere, Category = Danage)
		float mAttackDamage = 10.0f;
};
