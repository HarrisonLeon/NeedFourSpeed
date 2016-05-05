// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameFramework/Character.h"
#include "Weapon.h"
#include "ShipCharacter.generated.h"

UCLASS()
class NEEDFOURSPEED_API AShipCharacter : public ACharacter
{
	GENERATED_BODY()

	/* The mesh component */
	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* ShipMeshComponent;

	UPROPERTY(VisibleAnywhere)
		float MaximumVelocity;

public:
	// Sets default values for this pawn's properties
	AShipCharacter();

	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaSeconds) override;

	// Called to bind functionality to input
	//virtual void SetupPlayerInputComponent(class UInputComponent* InputComponent) override;

	void EquipWeapon(TSubclassOf<class AWeapon> WeaponClass);

	float ReceiveDamage(float Damage, AController* EventInstigator, AActor*DamageCauser);

	void ShowDamagePopUp(int32 damageTaken);

	void ShowPointsPopUp(int32 pointsAdded);

	UFUNCTION()
		void MoveForward(float Value);

	UFUNCTION()
		void MoveRight(float Value);

	UFUNCTION()
		void Aim(float ForwardValue, float RightValue);

	UFUNCTION()
		void Fire(FVector AimDirection);

	UFUNCTION()
		void StopFire();

	UFUNCTION()
		void Dash();

	UFUNCTION()
		void DashStop();

	UFUNCTION()
		void Die();

	UFUNCTION(BlueprintImplementableEvent)
		void ShowPlayerHUD();

	UFUNCTION(BlueprintImplementableEvent)
		void SetPlayerVisibility(int32 index);

	UFUNCTION(BlueprintImplementableEvent)
		void SetPlayerHealth(float health);

	UFUNCTION(BlueprintImplementableEvent)
		void SetPlayerScore(int32 score);

	UFUNCTION(BlueprintImplementableEvent)
		void SetPlayerAmmo(int32 ammo);

	UFUNCTION(BlueprintImplementableEvent)
		void CreatePlayerHUD();

	UFUNCTION(BlueprintImplementableEvent)
		void CreatePopUpText(const FString& s, FColor color);

	UFUNCTION(BlueprintImplementableEvent)
		void ShowEndGameMenu(int32 playerID);

	UAudioComponent* PlaySound(USoundCue* sound);

	UPROPERTY(EditDefaultsOnly, Category = Config)
	class USoundCue* mDestroySound;


	static const FName MoveForwardBinding;
	static const FName MoveRightBinding;
	static const FName AimForwardBinding;
	static const FName AimRightBinding;
	static const FName FireBinding;
	static const FName StopFireBinding;

	//Weapon stuff
	UPROPERTY(EditDefaultsOnly, Category = Spawn)
		TSubclassOf<class AWeapon> mWeaponClass;

	AWeapon* mCurrentWeapon;

	UPROPERTY(EditDefaultsOnly,Category=Mesh)
		TArray<UMaterialInstance*> mMaterials;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = PlayerIndex)
		int32 mPlayerIndex;

	void SetPlayerMaterial();
	void SetPlayerIndex(int32 index);
	int32 GetPlayerIndex() { return mPlayerIndex; }

protected:
	UPROPERTY(EditDefaultsOnly, Category = Effects) UParticleSystem* ExplosionFX;

	UPROPERTY(EditDefaultsOnly, Category = Effects) UParticleSystem* SpawnFX;

private:

	bool isBoosting = false;

	FVector PreviousVelocity;
	FRotator currentRotation;

	FTimerHandle BoostTimerHandle;

	//This dynamic material is used to set the material of the character 
	UMaterialInstanceDynamic* DynamicMaterial;
};
