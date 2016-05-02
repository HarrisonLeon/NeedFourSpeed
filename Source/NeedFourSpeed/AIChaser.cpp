// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "AIChaser.h"
#include "ShipCharacter.h"
#include "AIChaserController.h"

// Sets default values
AAIChaser::AAIChaser()
{
	AIControllerClass = AAIChaserController::StaticClass();
	GetCapsuleComponent()->SetCapsuleSize(2.f,2.f,false);
	mSphereComponent = CreateDefaultSubobject<USphereComponent>(TEXT("USphereComponent"));
	mSphereComponent->SetSphereRadius(40.0f);
	//mSphereComponent->OnComponentBeginOverlap.AddDynamic(this, &AAIChaser::OnOverlap);
	mSphereComponent->bGenerateOverlapEvents = true;
	mSphereComponent->AttachTo(RootComponent);
}

// Called when the game starts or when spawned
void AAIChaser::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AAIChaser::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AAIChaser::StartAttack()
{

}

void AAIChaser::DoDamageToPlayer()
{

}

void AAIChaser::StopAttack()
{

}

void AAIChaser::Die()
{
	Super::Die();
}

void AAIChaser::OnOverlap(class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if ((OtherActor != NULL) && OtherActor->IsA(AShipCharacter::StaticClass()))
	{
		Cast<AShipCharacter>(OtherActor)->ReceiveDamage(100.0f, nullptr, this);
		Die();
	}
}






