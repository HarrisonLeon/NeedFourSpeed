// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "ShipCharacter.h"
#include "ShipPlayerController.h"
#include "NeedFourSpeedGameMode.h"
#include "Weapon.h"
#include "WeaponPickUp.h"
#include "ShipPlayerState.h"
#include "Engine.h"

#define print(text, color) if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 1.5, color, text)

const FName AShipCharacter::MoveForwardBinding("MoveForward");
const FName AShipCharacter::MoveRightBinding("MoveRight");
const FName AShipCharacter::AimForwardBinding("AimForward");
const FName AShipCharacter::AimRightBinding("AimRight");
const FName AShipCharacter::StopFireBinding("StopFire");

AShipCharacter::AShipCharacter()
{
	MaximumVelocity = 4000.0f;
	PreviousVelocity = FVector();
	currentRotation = FRotator(0.0f, 0.0f, 0.0f);

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//AutoPossessPlayer = EAutoReceiveInput::Player0;

	// Adjust CapsuleComponent
	GetCapsuleComponent()->InitCapsuleSize(50.0f, 50.0f);

	//Get player index
	//int32 pIndex=Cast<AShipPlayerController>(GetController())->GetPlayerIndex();
	static ConstructorHelpers::FObjectFinder<UStaticMesh> ShipMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));

	// Create the mesh component
	ShipMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ShipMesh"));
	ShipMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	ShipMeshComponent->SetStaticMesh(ShipMesh.Object);
	ShipMeshComponent->SetRelativeLocation(FVector(0.0f, 0.0f, -20.0f));
	ShipMeshComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AShipCharacter::BeginPlay()
{
	Super::BeginPlay();
	SetPlayerIndex(-1);
	SetPlayerMaterial();
	this->SetPlayerHealth(1.0f);
	this->SetPlayerVisibility(mPlayerIndex);
	AShipPlayerState* playerState = Cast<AShipPlayerState>(this->PlayerState);
	if (playerState)
	{
		AShipPlayerController* controller = Cast<AShipPlayerController>(GetOwner());
		if (controller)
		{
			AShipPlayerState* playerState = Cast<AShipPlayerState>((controller->PlayerState));
			if (playerState)
			{
				int32 score = playerState->GetScore();
				this->SetPlayerScore(score);
			}
		}
	}
	FVector spawnLoc = GetActorLocation();
	if (SpawnFX)
	{
		UGameplayStatics::SpawnEmitterAtLocation(this, SpawnFX, spawnLoc);
	}
	//this->SetPlayerAmmo(0);
}

void AShipCharacter::SetPlayerIndex(int32 index)
{
	//Get player previous index from the spawn queue if exists

	ANeedFourSpeedGameMode* gameMode = Cast<ANeedFourSpeedGameMode>(this->GetWorld()->GetAuthGameMode());
	if (gameMode)
	{
		TQueue<int32>& queue = gameMode->GetPlayerIndexSpawnQueue();
		if (!queue.IsEmpty())
		{
			int32 num;
			queue.Peek(num);
			mPlayerIndex = num;
			queue.Dequeue(num);
			num = 3;
		}
		else
		{
			//TODO: Remove this parameter
			static int pIndex = 0;
			mPlayerIndex = pIndex % 4;
			++pIndex;
		}
	}
}

void AShipCharacter::SetPlayerMaterial()
{
	//Get the player index for setting color
	if (mPlayerIndex == -1)
	{
		mPlayerIndex = 0;
	}
	int32 size=ShipMeshComponent->StaticMesh->Materials.Num();
	ShipMeshComponent->StaticMesh->Materials.Empty();
	int32 size2 = ShipMeshComponent->StaticMesh->Materials.Num();
	ShipMeshComponent->StaticMesh->Materials.Add(mMaterials[mPlayerIndex]);
}

// Called every frame
void AShipCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// Find movement direction
	const float ForwardValue = GetInputAxisValue(MoveForwardBinding);
	const float RightValue = GetInputAxisValue(MoveRightBinding);

	if (ForwardValue == 0.0f)
	{
		PreviousVelocity.X = 0.0f;
	}

	if (RightValue == 0.0f)
	{
		PreviousVelocity.Y = 0.0f;
	}
}

void AShipCharacter::ShowDamagePopUp(int32 damageTaken)
{
	FString damageString = "-";
	damageString.Append(FString::FromInt(damageTaken));
	CreatePopUpText(damageString, FColor::Red);
}

void AShipCharacter::ShowPointsPopUp(int32 pointsAdded)
{
	FString pointsPopUpText = "+";
	pointsPopUpText.Append(FString::FromInt(pointsAdded));
	CreatePopUpText(pointsPopUpText, FColor::Yellow);
}

float AShipCharacter::ReceiveDamage(float Damage, AController* EventInstigator, AActor*DamageCauser)
{
	AShipPlayerController* controller=Cast<AShipPlayerController>(GetController());
	if (controller)
	{
		//show popuptext damage
		ShowDamagePopUp(Damage);
		float damageReceived = Cast<AShipPlayerState>(controller->PlayerState)->ReceiveDamage(Damage, EventInstigator, DamageCauser);
	}
	return -1.0f;
}

void AShipCharacter::Die()
{
	PlaySound(mDestroySound);
	FVector DeathLoc = GetActorLocation();
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionFX, DeathLoc);

	//Delete current weapon
	if (mCurrentWeapon)
	{
		mCurrentWeapon->Destroy();
	}
	//Delete dynamic material (players material)
	if (DynamicMaterial)
	{
		ShipMeshComponent->StaticMesh->Materials.Remove(DynamicMaterial);
	}
	Cast<ANeedFourSpeedGameMode>(this->GetWorld()->GetAuthGameMode())->AddPlayerIndexToSpawnQueue(mPlayerIndex);
	//Delete player
	Destroy();
}

UAudioComponent* AShipCharacter::PlaySound(USoundCue* sound)
{
	UAudioComponent* AC = NULL;
	if (sound)
	{
		AC = UGameplayStatics::SpawnSoundAttached(sound, RootComponent);
		AC->bStopWhenOwnerDestroyed = false;
	}
	return AC;
}

void AShipCharacter::EquipWeapon(TSubclassOf<class AWeapon> WeaponClass)
{
	mWeaponClass = WeaponClass;
	//Spawn the player's weapon
	FActorSpawnParameters spawnParams;
	spawnParams.Owner = this;
	spawnParams.Instigator = this;
	AWeapon * spawnedWeapon = GetWorld()->SpawnActor<AWeapon>(mWeaponClass, spawnParams);
	if (spawnedWeapon)
	{
		spawnedWeapon->AttachRootComponentTo(ShipMeshComponent, FName(TEXT("NAME_None")), EAttachLocation::SnapToTarget);
		if (mCurrentWeapon)
		{
			AWeapon* oldWeapon = mCurrentWeapon;
			mCurrentWeapon = NULL;
			oldWeapon->Destroy();
		}
		mCurrentWeapon = spawnedWeapon;
	}

	//Draw ammo to HUD
	if (mCurrentWeapon)
	{
		this->SetPlayerAmmo(mCurrentWeapon->GetCurrentAmmo());
	}
}

void AShipCharacter::MoveForward(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		// find out which way is forward
		FRotator Rotation = GetControlRotation();
		FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::X);

		float DeltaTime = GetWorld()->GetDeltaSeconds();

		FVector NewVelocity = (PreviousVelocity + (DeltaTime * Value * 100000.0f * Direction));
		FVector ClampedVelocity = NewVelocity.GetClampedToMaxSize(MaximumVelocity) * (isBoosting ? 3.5f : 1.0f);

		GetCharacterMovement()->Velocity = ClampedVelocity;
		PreviousVelocity = GetCharacterMovement()->Velocity;

		FRotator AimDirection = FRotator(0.0f, NewVelocity.Rotation().Yaw, 0.0f);
		ShipMeshComponent->SetRelativeRotation(AimDirection);
	}
}

void AShipCharacter::MoveRight(float Value)
{
	if ((Controller) && (Value != 0.0f))
	{
		// find out which way is right
		const FRotator Rotation = GetControlRotation();
		const FVector Direction = FRotationMatrix(Rotation).GetScaledAxis(EAxis::Y);

		float DeltaTime = GetWorld()->GetDeltaSeconds();
		
		FVector NewVelocity = (PreviousVelocity + (DeltaTime * Value * 100000.0f * Direction));
		FVector ClampedVelocity = NewVelocity.GetClampedToMaxSize(MaximumVelocity) * (isBoosting ? 3.5f : 1.0f);

		GetCharacterMovement()->Velocity = ClampedVelocity;
		PreviousVelocity = GetCharacterMovement()->Velocity;

		FRotator AimDirection = FRotator(0.0f, NewVelocity.Rotation().Yaw, 0.0f);
		ShipMeshComponent->SetRelativeRotation(AimDirection);
	}
}

void AShipCharacter::Aim(float ForwardValue, float RightValue)
{
	if (!FMath::IsNearlyZero(ForwardValue) || !FMath::IsNearlyZero(RightValue))
	{
		FVector AimDirection = FVector(-ForwardValue, RightValue, 0.0f);
		Fire(AimDirection);
	}
}

void AShipCharacter::Fire(FVector AimDirection)
{
	if (mCurrentWeapon)
	{
		mCurrentWeapon->Fire(AimDirection);
	}
}

void AShipCharacter::StopFire()
{
	if (mCurrentWeapon)
	{
		mCurrentWeapon->StopFire();
	}
}

void AShipCharacter::Dash()
{
	isBoosting = true;
	GetWorld()->GetTimerManager().SetTimer(BoostTimerHandle, this, &AShipCharacter::DashStop, 0.2f, false);
}

void AShipCharacter::DashStop()
{
	isBoosting = false;
}
