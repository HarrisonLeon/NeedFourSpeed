// Fill out your copyright notice in the Description page of Project Settings.

#include "NeedFourSpeed.h"
#include "GoalNode.h"
#include "ShipPlayerState.h"
#include "ShipPlayerController.h"
#include "ShipPlayerState.h"


AGoalNode::AGoalNode() {

}

void AGoalNode::SetSpawnManager(ASpawnManager* sm) {
	this->sm = sm;
}

void AGoalNode::PickUp(AShipCharacter* player) {
	//Cast<AShipPlayerState>(player->GetController()->PlayerState)->ScoreGoalNode();
	AShipPlayerController* controller = Cast<AShipPlayerController>(player->GetController());
	if (controller) {
		AShipPlayerState* playerState = Cast<AShipPlayerState>(controller->PlayerState);
		if (playerState) {
			playerState->ScoreGoalNode(player);
		}
	}
	sm->SpawnGoalNode();
}


