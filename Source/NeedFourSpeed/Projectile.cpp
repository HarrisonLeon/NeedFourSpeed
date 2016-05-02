// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "ShipCharacter.h"
#include "AICharacter.h"
#include "Engine.h"
#include "Projectile.h"

// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create mesh component for the projectile sphere
	ProjectileMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	//ProjectileMesh->AttachTo(RootComponent);
	ProjectileMesh->BodyInstance.SetCollisionProfileName("Projectile");		// set up a notification for when this component hits something
	RootComponent = ProjectileMesh;

	// Use a ProjectileMovementComponent to govern this projectile's movement
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovement0"));
	ProjectileMovement->UpdatedComponent = ProjectileMesh;
	ProjectileMovement->InitialSpeed = 3000.f;
	ProjectileMovement->MaxSpeed = 3000.f;
	ProjectileMovement->bRotationFollowsVelocity = true;
	ProjectileMovement->bShouldBounce = false;
	ProjectileMovement->ProjectileGravityScale = 0.f; // No gravity

	//Initialize the sphere component
	mCapsuleComponent = CreateDefaultSubobject<UCapsuleComponent>(TEXT("USphereComponent"));
	mCapsuleComponent->SetCapsuleRadius(30.0f);
	//mCapsuleComponent->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);
	mCapsuleComponent->OnComponentBeginOverlap.AddDynamic(this, &ABullet::OnOverlap);
	mCapsuleComponent->bGenerateOverlapEvents = true;
	mCapsuleComponent->AttachTo(RootComponent);

	mLifeTime = 4.0f;
}

// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AProjectile::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnOverlap(OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherActor != Cast<AActor>(Instigator))&& (!OtherActor->IsA(ABullet::StaticClass())))
	{
		//Do damage if it is a player or AI unit
		if (OtherActor->IsA(AShipCharacter::StaticClass()))
		{
			Cast<AShipCharacter>(OtherActor)->ReceiveDamage(mDamage, nullptr, Instigator);
		}
		else if (OtherActor->IsA(AAICharacter::StaticClass()))
		{
			Cast<AAICharacter>(OtherActor)->ReceiveDamage(mDamage, nullptr, Instigator);
		}
		Kill();
	}
}

