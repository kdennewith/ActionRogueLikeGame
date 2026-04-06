// Fill out your copyright notice in the Description page of Project Settings.


#include "RLGameMode.h"

#include "Player/RLPlayerController.h"

ARLGameMode::ARLGameMode()
{	/** Adding the Character controller class to the Game Mode so it's set for the player */
	PlayerControllerClass = ARLPlayerController::StaticClass();
}
