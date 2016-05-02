// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "ShipPlayerState.h"
#include "ShipPlayerController.h"
#include "ShipCharacter.h"
#include "NeedFourSpeedGameMode.h"

AShipPlayerState::AShipPlayerState() {
	mHealth = mMaxHealth;
	mScore = 0;
}

void AShipPlayerState::ScoreGoalNode(AShipCharacter* player) {
	mScore += mGoalScore;
	if (player) {
		player->SetPlayerScore(mScore);
	}
	if (mScore >= mMaxScore) {
		
	}
}

void AShipPlayerState::ScoreKill(AShipCharacter* player) {
	mScore += mKillScore;
	if (player) {
		player->SetPlayerScore(mScore);
	}
	if (mScore >= mMaxScore) {

	}
}

float AShipPlayerState::ReceiveDamage(float Damage, AController* EventInstigator, AActor*DamageCauser) {
	if (Damage != 0.0f) {
		mHealth -= Damage;
		AShipPlayerController* OwnerController = Cast<AShipPlayerController>(GetOwner());
		if (OwnerController) {
			AShipCharacter* otherChar = Cast<AShipCharacter>(DamageCauser);
			AShipCharacter* player = Cast<AShipCharacter>(OwnerController->GetPawn());
			if (player) {
				if (mHealth < 0.0f) { mHealth = 0.0f; }
				player->SetPlayerHealth(mHealth / mMaxHealth);
			}
			if (mHealth <= 0.0f) {
				//ADD SCORE TO THE OTHER PLAYER
				AShipCharacter* otherChar = Cast<AShipCharacter>(DamageCauser);
				if (otherChar) {
					AShipPlayerController* otherController = Cast<AShipPlayerController>(otherChar->GetController());
					if (otherController) {
						AShipPlayerState* otherPlayerState = Cast<AShipPlayerState>(otherController->PlayerState);
						if (otherPlayerState) {
							otherPlayerState->ScoreKill(otherChar);
							//otherChar->SetPlayerScore(mScore);
						}
					}
				}
				//KILL THIS PLAYER
				if (player) {
					player->Die();
					Cast<ANeedFourSpeedGameMode>(GetWorld()->GetAuthGameMode())->GetCustomCamera()->StopTracking(OwnerController);
					GetWorldTimerManager().SetTimer(SpawnHandle, this, &AShipPlayerState::Respawn, 2.0f, false);
				}
			}
		}
	}
	return Damage;
}

void AShipPlayerState::Respawn() {
	AShipPlayerController* OwnerController = Cast<AShipPlayerController>(GetOwner());
	if (OwnerController) {
		ANeedFourSpeedGameMode* gamemode = Cast<ANeedFourSpeedGameMode>(GetWorld()->GetAuthGameMode());
		if (gamemode) {
			gamemode->RestartPlayer(OwnerController);
			Cast<ANeedFourSpeedGameMode>(GetWorld()->GetAuthGameMode())->GetCustomCamera()->StartTracking(OwnerController);
			mHealth = mMaxHealth;
		}
	}
}
