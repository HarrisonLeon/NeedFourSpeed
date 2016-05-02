// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "Engine.h"
#include "PickUp.h"


// Sets default values
APickUp::APickUp()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	mSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("RootComponent"));
	RootComponent = mSphereComponent;
	mSphereComponent->InitSphereRadius(80.0f);
	mSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &APickUp::OnOverlapBegin);
	mSphereComponent->OnComponentEndOverlap.AddDynamic(this, &APickUp::OnOverlapEnd);
	mSphereComponent->bGenerateOverlapEvents = true;
	mRotationSpeed = 6.0f;
}

// Called when the game starts or when spawned
void APickUp::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APickUp::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FRotator rot = this->GetActorRotation();
	rot.Yaw += mRotationSpeed;
	this->SetActorRotation(rot);
}

void APickUp::OnOverlapBegin(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (!OtherActor->IsA(AShipCharacter::StaticClass())) return;
	// Only add impulse and destroy projectile if we hit a physics
	if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL) && OtherComp->IsSimulatingPhysics())
	{
		OtherComp->AddImpulseAtLocation(GetVelocity() * 20.0f, GetActorLocation());
	}
	AShipCharacter* player = Cast<AShipCharacter>(OtherActor);
	PickUp(player);
	Destroy();
}

void APickUp::OnOverlapEnd(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{

}

void APickUp::PickUp(AShipCharacter* player)
{

}

