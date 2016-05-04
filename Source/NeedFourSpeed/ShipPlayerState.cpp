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
		//Show pop up with points added
		player->ShowPointsPopUp(mGoalScore);
		player->SetPlayerScore(mScore);
	}
	CheckEndGame();
}

void AShipPlayerState::ScoreKill(AShipCharacter* player) {
	mScore += mKillScore;
	if (player) {
		//Show pop up with points added
		player->ShowPointsPopUp(mKillScore);
		player->SetPlayerScore(mScore);
	}
	CheckEndGame();
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

void AShipPlayerState::CheckEndGame() {
	if (mScore >= mMaxScore) {
		UGameplayStatics::SetGamePaused(GetWorld(), true);
		AShipPlayerController* OwnerController = Cast<AShipPlayerController>(GetOwner());
		if (OwnerController) {
			AShipCharacter* player = Cast<AShipCharacter>(OwnerController->GetPawn());
			if (player) {
				Cast<ANeedFourSpeedGameMode>(GetWorld()->GetAuthGameMode())->GetCustomCamera()->ClearAllPlayers();
				player->ShowEndGameMenu(player->mPlayerIndex);
			}
		}
	}
}

