// Fill out your copyright notice in the Description page of Project Settings.


#include "RLPlayerController.h"

#include "RLInteractionComponent.h"

ARLPlayerController::ARLPlayerController()
{
	InteractionComponent = CreateDefaultSubobject<URLInteractionComponent>(TEXT("InteractionComp"));
}
