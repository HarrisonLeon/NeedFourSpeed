// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "ShipCharacter.h"
#include "AICharacter.h"
#include "Engine.h"
#include "Ray.h"


// Sets default values
ARay::ARay()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// Create mesh component for the ray 
	RayMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("ProjectileMesh0"));
	RayMesh->AttachTo(RootComponent);
	RayMesh->BodyInstance.SetCollisionProfileName("Projectile");
	RayMesh->OnComponentBeginOverlap.AddDynamic(this, &ARay::OnOverlap);		// set up a notification for when this component hits something
	RayMesh->SetWorldScale3D(FVector(15,15,15));
	RootComponent = RayMesh;
	mRayScaleSpeed = 1.3f;
	mLifeTime = 1.5f;
}

// Called when the game starts or when spawned
void ARay::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void ARay::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );

	/*Scale the ray until it is too big then destroy*/
	FVector scale= RayMesh->GetRelativeTransform().GetScale3D();
	if (mMaxXScale > scale.X)
	{
		scale.X *= mRayScaleSpeed;
		RayMesh->SetRelativeScale3D(scale);
	}

	//Move the ray forward while scaling
	FVector forward=this->GetActorForwardVector();
	this->SetActorLocation(this->GetActorLocation() + forward*mRayBackSpeed*DeltaTime);
}

void ARay::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	Super::OnOverlap(OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherActor != Cast<AActor>(Instigator)))
	{
		//Do damage if it is a player or AI unit
		if (OtherActor->IsA(AShipCharacter::StaticClass()))
		{
			if (Instigator->IsA(AShipCharacter::StaticClass()))
			{
				Cast<AShipCharacter>(OtherActor)->ReceiveDamage(mDamage, nullptr, Instigator);
			}
		}
		else if (OtherActor->IsA(AAICharacter::StaticClass()))
		{
			if (Instigator->IsA(AShipCharacter::StaticClass()))
			{
				Cast<AAICharacter>(OtherActor)->ReceiveDamage(mDamage, nullptr, Instigator);
			}
		}
	}
}

