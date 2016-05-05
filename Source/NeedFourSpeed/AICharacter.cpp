// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "AICharacterController.h"
#include "NeedFourSpeedGameMode.h"
#include "AICharacter.h"


// Sets default values
AAICharacter::AAICharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Set controller of actor
	AIControllerClass = AAICharacterController::StaticClass();

	//Initialize the mesh component
	static ConstructorHelpers::FObjectFinder<UStaticMesh> AIMesh(TEXT("/Game/TwinStick/Meshes/TwinStickUFO.TwinStickUFO"));

	// Create the mesh component
	mAIMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("AIMesh"));
	mAIMeshComponent->SetCollisionProfileName(UCollisionProfile::Pawn_ProfileName);
	//mAIMeshComponent->SetStaticMesh(mAIMesh);
	mAIMeshComponent->AttachTo(RootComponent);
	mAIMeshComponent->SetWorldScale3D(FVector(1, 1, 1));

	//Set the radius of the collision component
	GetCapsuleComponent()->SetCapsuleHalfHeight(56.0f);
	GetCapsuleComponent()->SetCapsuleRadius(56.0f);
	GetCapsuleComponent()->bGenerateOverlapEvents = true;
}

// Called when the game starts or when spawned
void AAICharacter::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void AAICharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

}

// Called to bind functionality to input
void AAICharacter::SetupPlayerInputComponent(class UInputComponent* InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

}

float AAICharacter::ReceiveDamage(float Damage, AController* EventInstigator, AActor*DamageCauser)
{
	if (Damage > 0.0f)
	{
		mHealth -= Damage;
		if (mHealth <= 0.0f)
		{
			StopAttack();
			Die();
		}
	}
	return Damage;
}

void AAICharacter::StartAttack()
{

}

void AAICharacter::DoDamageToPlayer()
{

}

void AAICharacter::StopAttack()
{

}

UAudioComponent* AAICharacter::PlaySound(USoundCue* sound)
{
	UAudioComponent* AC = NULL;
	if (sound)
	{
		AC = UGameplayStatics::SpawnSoundAttached(sound, RootComponent);
		AC->bStopWhenOwnerDestroyed = false;
	}
	return AC;
}

void AAICharacter::Die()
{
	//Tell controller not to update
	if (GetController())
	{
		GetController()->UnPossess();
	}
	PlaySound(mDestroySound);
	FVector DeathLoc = GetActorLocation();
	UGameplayStatics::SpawnEmitterAtLocation(this, ExplosionFX, DeathLoc);
	Destroy();
}